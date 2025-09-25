/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:15:59 by macauchy          #+#    #+#             */
/*   Updated: 2025/09/23 09:28:59 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parser.hpp"
#include <cstdlib>
#include <cerrno>

# define SIZE_MAX ((size_t)-1)

Parser::Parser( void ) : _state(REQ_LINE), _chunkState(CHUNK_SIZE)
{
	_chunked = false;
	_expectedBodyLength = 0;
	_chunkBytesRemaining = 0;
	// _limitHeaderBytes = 8 * 1024; // 8 KB
	// _limitBodyBytes = 1 * 1024 * 1024; // 1 MB
	// _limitLineBytes = 4 * 1024; // 4 KB
}

Parser::Parser( const Parser& other )
{
	*this = other;
}

Parser	&Parser::operator=( const Parser &other )
{
	if (this != &other)
	{
		_state = other._state;
		_buffer = other._buffer;
		_current = other._current;
		_expectedBodyLength = other._expectedBodyLength;
		_chunked = other._chunked;
		_limitHeaderBytes = other._limitHeaderBytes;
		_limitBodyBytes = other._limitBodyBytes;
		_limitLineBytes = other._limitLineBytes;
		_chunkBytesRemaining = other._chunkBytesRemaining;
		_lastChunkSeen = other._lastChunkSeen;
	}
	return *this;
}

Parser::~Parser( void )
{
}

//toLower
static std::string	_toLower( const std::string &s )
{
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

bool	Parser::isComplete( void ) const
{
	return (_state == COMPLETE);
}

Request	Parser::getRequest( void ) const
{
	return (_current);
}

void	Parser::reset( void )
{
	_state = REQ_LINE;
	_chunkState = CHUNK_SIZE;
	_current.reset();
	_expectedBodyLength = 0;
	_chunkBytesRemaining = 0;
}

void	Parser::setLimits( size_t headerBytes, size_t bodyBytes, size_t lineBytes )
{
	_limitHeaderBytes = headerBytes;
	_limitBodyBytes = bodyBytes;
	_limitLineBytes = lineBytes;
}

void	Parser::_setError( int code, const std::string &message )
{
	_current.setError();
	_current.setErrorCode(code);
	_current.setErrorMessage(message);
	_current.markComplete();
	_state = COMPLETE; // Stop further parsing
}

bool	Parser::feed( const std::string &data, const Config &cfg)
{
	_buffer += data;

	// std::cerr << "[DEBUG BODY BITES MAX] = " << _limitBodyBytes << std::endl;
	try
	{
		// Request Line
		if (_state == REQ_LINE)
		{
			// Protect against overly long lines
			size_t pos = _buffer.find("\r\n");
			if (pos != std::string::npos && static_cast<size_t>(pos) > _limitLineBytes)
				throw HttpParseError(400, "Request line too long");
			if (pos == std::string::npos)
				return false;

			_parseRequestLine(_buffer.substr(0, pos), cfg);
			// Erase the request line including the terminating CRLF so headers start cleanly
			_buffer.erase(0, pos + 2);
			_state = HEADERS;
		}

		// Headers
		if (_state == HEADERS)
		{
			// Protect against overly large headers (slowloris attack)
			if (_buffer.size() > _limitHeaderBytes)
				throw HttpParseError(431, "Headers too large");

			size_t	end = _buffer.find("\r\n\r\n");
			if (end == std::string::npos)
			{
				// Special-case: empty header block where buffer starts with CRLF (i.e., "\r\n\r\n" was split so after removing request line we may have "\r\n")
				if (_buffer.size() >= 2 && _buffer.substr(0, 2) == "\r\n")
					end = 0; // empty headers
				else
					return false;
			}

			_parseHeaderBlock(_buffer.substr(0, end));
			// If end == 0 we need to erase the terminating sequence length (4) to consume the CRLFCRLF
			_buffer.erase(0, end + 4);
			
			// Check for body indicators
			if (_chunked || _expectedBodyLength > 0)
			{
				_state = BODY;
				if (_chunked)
				{
					_chunkState = CHUNK_SIZE;
					_chunkBytesRemaining = 0;
				}
			}
			else
			{
				// No body, request is complete
				_current.markComplete();
				_state = COMPLETE;
				return true;
			}
		}

		// Body
		if (_state == BODY)
		{
			if (_chunked)
			{
				if (_decodeChunked())
				{
					_state = COMPLETE;
					_current.markComplete();
					return true;
				}
			}
			else if (_parseBody())
			{
				_state = COMPLETE;
				_current.markComplete();
				return true;
			}
		}
	}
	catch (const HttpParseError &e)
	{
		_setError(e.code, e.what());
		// std::cerr << "[Parser] Error: " << e.what() << " (code " << e.code << ")" << std::endl;
		// Inform caller that parsing is complete (with an error). This lets the server
		// generate an appropriate error response and close the connection instead of
		// continuing to feed the same binary data back into the parser.
		return true;
	}
	catch (const std::exception &e)
	{
		_setError(400, "Bad Request");
		// std::cerr << "[Parser] Exception: " << e.what() << std::endl;
		// Treat generic exceptions as completed (bad) requests so the caller can react.
		return true;
	}
	return false;
}

void	Parser::_parseRequestLine( const std::string &line, const Config &cfg)
{
	// Format: METHOD SP URI SP VERSION
	// Example: GET /index.html HTTP/1.1

	// enforce line length limit
	if (line.length() > _limitLineBytes)
		throw HttpParseError(400, "Request line too long");

	std::istringstream	ss(line);
	std::string method, uri, version;
	ss >> method >> uri >> version;
	_current.setMethod(method);
	_current.setUri(uri);
	_current.setVersion(version);

	const Location *loc = cfg.getLocationByPath(uri);
	size_t limit = cfg.getClientMaxBodySize();
	if (loc)
	{
		size_t locLimit = loc->getClientMaxBodySize();
		if (locLimit > 0)
			limit = locLimit;
	}
	_limitBodyBytes = limit;

	// Basic validation
	if (method.empty() || uri.empty() || version.empty())
		throw HttpParseError(400, "Malformed request line");

	// Allowed methods
	if (method != "GET" && method != "POST" && method != "DELETE")
		throw HttpParseError(405, "Method Not Allowed");

	// Validate HTTP version
	if (version != "HTTP/1.1" && version != "HTTP/1.0")
		throw HttpParseError(505, "HTTP Version Not Supported");

	// Normalize path and extract query
	size_t	qpos = _current.getUri().find('?');
	if (qpos != std::string::npos)
	{
		// Query string present (e.g., /index.html?user=42)
		_current.setPath(_normalizePath(_current.getUri().substr(0, qpos)));
		_current.setQuery(_current.getUri().substr(qpos + 1));
	}
	else
	{
		// No query string present
		_current.setPath(_normalizePath(_current.getUri()));
		_current.setQuery("");
	}

	// Reject weird characters in path
	for (size_t i = 0; i < _current.getPath().length(); i++)
	{
		unsigned char c = static_cast<unsigned char>(_current.getPath()[i]);
		if (c < 32 && c != '\t') // Allow tab
			throw HttpParseError(400, "Invalid character in path");
	}
}

void	Parser::_parseHeaderBlock( const std::string &rawHeaders )
{
	std::istringstream	ss(rawHeaders);
	std::string 		line;

	bool	sawContentLength = false; 	// track if Content-Length was seen and
	bool	sawTransferEncoding = false;// track if Transfer-Encoding was seen to prevent http smuggling

	while (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1); // Remove trailing \r (C++98 safe)
		if (line.empty())
			break ; // Skip empty lines (shouldn't happen here)

		// Check line length
		if (line.size() > _limitLineBytes)
			throw HttpParseError(400, "Header line too long");

		// Split at first colon
		size_t	colon = line.find(':');
		if (colon == std::string::npos)
			throw HttpParseError(400, "Malformed header line");

		std::string	key, value;
		key = line.substr(0, colon);
		value = line.substr(colon + 1);

		// Trim value (i.g., "  value  " -> "value")
		size_t start = value.find_first_not_of(" \t");
		size_t end = value.find_last_not_of(" \t");
		
		// If value is all spaces/tabs, set to empty string
		if (start == std::string::npos)
			value.clear();
		else
			value = value.substr(start, end - start + 1); // Trim spaces/tabs

		_current.setHeader(key, value);

		// Special handling for Content-Length and Transfer-Encoding (Bookkeeping)
		std::string	k = key;
		std::transform(k.begin(), k.end(), k.begin(), ::tolower);
		if (k == "content-length")
		{
			if (sawContentLength)
			{
				_setError(400, "Multiple Content-Length headers");
				return;
			}
			sawContentLength = true;
			
			// Parse Content-Length value
			// const std::string	&v = _current.getHeader("content-length");
			const std::string& v = value;
			if (v.empty())
			{
				_setError(400, "Empty Content-Length header");
				return;
			}

			// Ensure Content-Length is numeric
			for (size_t i = 0; i < v.length(); ++i)
			{
				if (!std::isdigit(static_cast<unsigned char>(v[i])))
				{
					_setError(400, "Non-numeric Content-Length");
					return;
				}
			}

			// Convert to long long using strtoll (C++98 safe) with errno checks
			errno = 0;
			const char *cstr = v.c_str();
			char *endptr = NULL;
			long long tmp = std::strtoll(cstr, &endptr, 10);
			if (errno == ERANGE)
			{
				_setError(400, "Content-Length out of range");
				return;
			}
			if (endptr == cstr || *endptr != '\0')
			{
				_setError(400, "Invalid Content-Length");
				return;
			}
			if (tmp < 0 || static_cast<size_t>(tmp) > _limitBodyBytes)
			{
				_setError(413, "Content-Length too large");
				return;
			}
			if (_limitBodyBytes && static_cast<size_t>(tmp) > _limitBodyBytes)
			{
				_setError(413, "Content-Length too large");
				return;
			}
			_expectedBodyLength = static_cast<size_t>(tmp); // Safe cast after checks
			if (_expectedBodyLength > _limitBodyBytes)
			{
				_setError(413, "Content-Length exceeds limit");
				return;
			}
		}
		else if (k == "transfer-encoding")
		{
			if (sawTransferEncoding)
			{
				_setError(400, "Multiple Transfer-Encoding headers");
				return;
			}
			sawTransferEncoding = true;
			if (_current.getHeader("transfer-encoding") != "chunked")
			{
				_setError(501, "Unsupported Transfer-Encoding");
				return;
			}
			_chunked = true;
			_lastChunkSeen = false;
			_chunkBytesRemaining = SIZE_MAX; // Indicate we need to read a new chunk
		}
		else if (k == "cookie")
		{
			_current.setHeader("cookie", value);
		}

	}
	
	// HTTP/1.1 requires Host header
	if (_current.getVersion() == "HTTP/1.1" && !_current.hasHeader("host"))
		_setError(400, "Missing Host header");

	// Prevent HTTP request smuggling
	if (sawContentLength && sawTransferEncoding)
		_setError(400, "Both Content-Length and Transfer-Encoding headers present");
}

bool	Parser::_decodeChunked( void )
{
	// Deterministic chunked decoding state machine. Uses _chunkState to track where
	// we are: reading chunk size lines, reading chunk data, or parsing trailers after
	// the terminating 0-sized chunk.
	while (true)
	{
		if (_chunkState == CHUNK_SIZE)
		{
			// Look for chunk-size line terminated by CRLF
			size_t pos = _buffer.find("\r\n");
			if (pos == std::string::npos)
			{
				if (_limitLineBytes && _buffer.size() > _limitLineBytes)
					throw HttpParseError(400, "Chunk size line too long");
				return false; // need more data
			}

			std::string sizeLine = _buffer.substr(0, pos);
			if (_limitLineBytes && sizeLine.size() > _limitLineBytes)
				throw HttpParseError(400, "Chunk size line too long");
			// consume size line + CRLF
			_buffer.erase(0, pos + 2);

			// strip extensions
			size_t semi = sizeLine.find(';');
			std::string hexStr = (semi == std::string::npos) ? sizeLine : sizeLine.substr(0, semi);
			_trim(hexStr);
			if (hexStr.empty())
				throw HttpParseError(400, "Empty chunk size");

			unsigned long long chunkSize = 0;
			if (!_parseHex(hexStr, chunkSize))
				throw HttpParseError(400, "Invalid chunk size");

			// enforce body size limits
			if (_limitBodyBytes)
			{
				size_t used = _current.getBody().size();
				if (used > _limitBodyBytes)
					throw HttpParseError(413, "Body size limit exceeded");
				size_t allowed = _limitBodyBytes - used;
				if (chunkSize > static_cast<unsigned long long>(allowed))
					throw HttpParseError(413, "Chunk size exceeds body limit");
			}

			if (chunkSize == 0)
			{
				// final chunk, move to trailers
				_lastChunkSeen = true;
				_chunkBytesRemaining = 0;
				_chunkState = CHUNK_TRAILERS;
				continue; // handle trailers in next loop iteration
			}
			// prepare to read chunk data
			_chunkBytesRemaining = static_cast<size_t>(chunkSize);
			_chunkState = CHUNK_DATA;
			continue;
		}

		if (_chunkState == CHUNK_DATA)
		{
			// Need chunk data + trailing CRLF
			size_t totalNeeded = _chunkBytesRemaining + 2; // data + CRLF
			// If we don't even have the minimal CRLF yet, wait for more data
			if (_buffer.size() < 2)
				return false;

			// Find the next CRLF in buffer
			size_t crlfPos = _buffer.find("\r\n");
			if (crlfPos == std::string::npos)
			{
				// No CRLF present yet
				if (_buffer.size() < totalNeeded)
					return false; // need more data
				// We have enough bytes but no CRLF -> malformed
				throw HttpParseError(400, "Missing CRLF after chunk data");
			}

			if (crlfPos < _chunkBytesRemaining)
			{
				// Early CRLF found before declared chunk size: tolerate by treating actual data length as crlfPos
				_current.appendToBody(_buffer.substr(0, crlfPos));
				_buffer.erase(0, crlfPos + 2); // consume up to CRLF
				// reset and continue with next chunk size
				_chunkBytesRemaining = SIZE_MAX;
				_chunkState = CHUNK_SIZE;
				continue;
			}
			else if (crlfPos == _chunkBytesRemaining)
			{
				// Expected case: exact CRLF after chunk data
				_current.appendToBody(_buffer.substr(0, _chunkBytesRemaining));
				_buffer.erase(0, _chunkBytesRemaining + 2);
				_chunkBytesRemaining = SIZE_MAX;
				_chunkState = CHUNK_SIZE;
				continue;
			}
			else
			{
				// CRLF occurs after the declared data length -> malformed
				throw HttpParseError(400, "Missing CRLF after chunk data");
			}
		}

		if (_chunkState == CHUNK_TRAILERS)
		{
			// If next bytes are CRLF this means there are no trailers (empty trailer block)
			if (_buffer.size() >= 2 && _buffer.substr(0, 2) == "\r\n")
			{
				// consume terminating CRLF and finish
				_buffer.erase(0, 2);
				_current.markComplete();
				_state = COMPLETE;
				return true;
			}

			// Look for end of trailers (CRLFCRLF)
			size_t end = _buffer.find("\r\n\r\n");
			if (end == std::string::npos)
			{
				// no full trailers yet
				if (_limitHeaderBytes && _buffer.size() > _limitHeaderBytes)
					throw HttpParseError(431, "Chunk trailers too large");
				return false; // need more data
			}

			std::string trailers = _buffer.substr(0, end);
			_buffer.erase(0, end + 4); // consume trailers + CRLFCRLF

			if (!trailers.empty())
			{
				size_t start = 0;
				while (start < trailers.size())
				{
					size_t eol = trailers.find("\r\n", start);
					if (eol == std::string::npos)
						eol = trailers.size();
					std::string line = trailers.substr(start, eol - start);
					start = (eol == trailers.size()) ? trailers.size() : eol + 2;
					if (line.empty())
						continue;
					std::string key, value;
					if (!_parseHeaderLine(line, key, value))
						throw HttpParseError(400, "Malformed trailer line");
					std::string lowerK = _toLower(key);
					_current.setTrailer(lowerK, value);
					if (_current.getHeaders().find(lowerK) == _current.getHeaders().end())
						_current.setHeader(lowerK, value);
				}
			}

			_current.markComplete();
			_state = COMPLETE;
			return true;
		}

		// Should never reach here
		throw HttpParseError(500, "Internal chunked decoding error");
	}

	return false; // unreachable
}

bool	Parser::_parseHeaderLine( const std::string &line, std::string &key, std::string &value )
{
	// Split at first colon
	size_t	colon = line.find(':');
	if (colon == std::string::npos)
		return (false);

	// Trim key and value
	key = line.substr(0, colon);
	value = line.substr(colon + 1);
	_trim(key);
	_trim(value);
	return (true);
}

void	Parser::_trim( std::string &s ) const
{
	// Trim leading/trailing whitespace (spaces, tabs and CR/LF)
	size_t a = s.find_first_not_of(" \t\r\n");
	if (a == static_cast<size_t>(-1) || a == std::string::npos)
	{
		// all whitespace -> empty string
		s.clear();
		return;
	}
	size_t b = s.find_last_not_of(" \t\r\n");
	s = s.substr(a, b - a + 1);
}

bool	Parser::_parseBody( void )
{
	// Content-Length based body
	if (_buffer.size() < _expectedBodyLength)
		return (false); // Need more data
	
	// Append body data
	_current.appendToBody(_buffer.substr(0, _expectedBodyLength));
	_buffer.erase(0, _expectedBodyLength);
	return (true); // Body complete
}

bool	Parser::_parseHex( const std::string &s, unsigned long long &out ) const
{
	if (s.empty())
		return (false);

	unsigned long long result = 0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if (!_isHex(c))
			return (false);
		result *= 16;
		if (c >= '0' && c <= '9')
			result += (c - '0');
		else if (c >= 'a' && c <= 'f')
			result += (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			result += (c - 'A' + 10);
		// Prevent runaway values (sanity check)
		if (result > (1ULL << 60)) // arbitrary large limit
			return (false);
	}
	out = result;
	return (true);
}

std::string	Parser::_normalizePath( const std::string &rawPath ) const
{
	// Always treat as absolute path for routing
	std::vector<std::string>	parts;	// to hold path segments
	std::string			seg;    // current segment

	// Fast path: empty -> root
	if (rawPath.empty())
		return std::string("/");

	// Split path by '/' — iterate one past the end to capture trailing segment
	size_t len = rawPath.size();
	size_t j = 0; // segment start
	for (size_t i = 0; i <= len; ++i)
	{
		if (i == len || rawPath[i] == '/')
		{
			if (i > j) // non-empty segment
			{
				seg = rawPath.substr(j, i - j);
				if (seg == ".")
				{
					// skip current dir
				}
				else if (seg == "..")
				{
					if (!parts.empty())
						parts.erase(parts.end() - 1);
					// if parts empty, stay at root (do not add empty)
				}
				else
				{
					parts.push_back(seg);
				}
			}
			// move to next segment start (skip the '/')
			j = i + 1;
		}
	}

	// Reconstruct normalized path
	std::string	normalized = "/";
	for (size_t i = 0; i < parts.size(); ++i)
	{
		normalized += parts[i];
		if (i + 1 < parts.size())
			normalized += "/";
	}
	return normalized;
}

bool	Parser::_isHex( char c ) const
{
	return ( (c >= '0' && c <= '9') ||
			 (c >= 'a' && c <= 'f') ||
			 (c >= 'A' && c <= 'F') );
}

// ----------- TODO: Implement chunked body parsing methods ------------
