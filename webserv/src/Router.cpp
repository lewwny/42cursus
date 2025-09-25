/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:29:43 by macauchy          #+#    #+#             */
/*   Updated: 2025/09/12 15:50:46 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Router.hpp"
#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"

// No CTOR/DTOR needed, as Router is a static utility class.

bool	Router::isMethodAllowed( const std::string &method, const Location *loc, std::string &allowHeader )
{
	std::vector<std::string>	allowed;

	if (loc && !loc->getMethods().empty())
		allowed = loc->getMethods();
	else
	{
		// Default allowed methods if none specified
		allowed.push_back("GET");
		// allowed.push_back("POST");
		// allowed.push_back("DELETE");
	}

	// Build Allow header
	std::ostringstream	oss;
	for (size_t i = 0; i < allowed.size(); ++i)
	{
		if (i > 0)
			oss << ", ";
		oss << allowed[i];
	}
	allowHeader = oss.str();

	// Check if method is in allowed list
	for (size_t i = 0; i < allowed.size(); ++i)
	{
		if (allowed[i] == method)
			return (true);
	}
	return (false);
}

bool	Router::normalizePath( const std::string &in, std::string &out )
{
	std::vector<std::string>	parts;	// to hold path segments
	std::istringstream			iss(in);
	std::string					token;
	bool						isAbsolute = (!in.empty() && in[0] == '/');

	// Split path by '/'
	while (std::getline(iss, token, '/'))
	{
		if (token.empty() || token == ".")
		{
			// skip empty or current dir
			continue ;
		}
		else if (token == "..")
		{
			// Backtrack one segment if possible
			if (!parts.empty())
				parts.pop_back();
			else if (isAbsolute)
				return (false); // Attempt to go above root for absolute paths
			// For relative paths, allow going up
		}
		else
		{
			parts.push_back(token);
		}
	}
	
	// Reconstruct normalized path
	if (isAbsolute)
		out = "/";
	else
		out = "";
		
	for (size_t i = 0; i < parts.size(); ++i)
	{
		if (i > 0 || isAbsolute)
			out += "/";
		out += parts[i];
	}
	
	// Handle edge case: if path was just "/" or empty, make sure we return something sensible
	if (out.empty() && isAbsolute)
		out = "/";
	
	return (true);
}

Router::Decision	Router::decide( const Request &req, const ServerManager &sm)
{
	Decision	d;

	d.server = &selectServer(req, sm)->getConfig();

	// if (check_session(req))
	// {
	// 	std::cout << YELLOW << "[Router] Session cookie found." << RESET << std::endl;
	// 	std::cout << "Server id : " << 0 << std::endl;
	// 	std::cout << "Session id : " << getSessionId(req) << std::endl;
	// 	try {
	// 	std::cout << "User id : " << cfg.getSession(getSessionId(req)) << std::endl;
	// 	}
	// 	catch (std::exception &e)
	// 	{}
	// 	std::cout << YELLOW << "--------------------" << RESET << std::endl;
	// }
	// Match location using prefix matching
	std::string	mount, rel;
	d.location = matchRoute(req.getUri(), selectServer(req, sm), mount, rel);
	d.mountUri = mount;
	d.relPath = rel;
	// std::cerr << "[DEBUG] Mount: " << d.mountUri << " RelPath: " << d.relPath << std::endl;
	// std::cerr << "[Router] Matched location: " << (d.location ? d.location->getPath() : "NULL") << " for URI: " << req.getUri() << std::endl;
	if (req.getError())
	{
		d.type = ACTION_ERROR;
		d.status = req.getErrorCode();
		d.reason = req.getErrorMessage();
		return (d);
	}
	if (!d.location)
	{
		std::cerr << "[Router] No matching location found for URI: " << req.getUri() << std::endl;
		d.type = ACTION_ERROR;
		d.status = 404;
		d.reason = "Not Found";
		return (d);
	}

	// Check method
	std::string	allowHeader;
	if (!isMethodAllowed(req.getMethod(), d.location, allowHeader))
	{
		std::cerr << "[Router] Method not allowed: " << req.getMethod() << std::endl;
		d.type = ACTION_ERROR;
		d.status = 405;
		d.reason = "Method Not Allowed";
		return (d);
	}
	if (!d.location->getReturn().empty())
	{
		int code = d.location->getReturn().substr(0, 3).empty() ? 0 : std::atoi(d.location->getReturn().substr(0, 3).c_str());
		std::string url = d.location->getReturn().substr(4);
		d.type = ACTION_REDIRECT;
		d.status = code;
		d.reason = "Redirect";
		d.redirectURL = url;
		return (d);
	}
	// Body size check in location then server
	long	maxBody = d.location->getClientMaxBodySize() > 0 
					? d.location->getClientMaxBodySize() 
					: d.server->getClientMaxBodySize();
	// std::cout << "[Router] Max body size for this request: " << maxBody << " bytes" << std::endl;
	if (req.getBody().size() > static_cast<size_t>(maxBody))
	{
		std::cerr << "[Router] Payload too large: " << req.getBody().size() << " > " << maxBody << std::endl;
		d.type = ACTION_ERROR;
		d.status = 413;
		d.reason = "Payload Too Large";
		return (d);
	}

	// Determine filesystem path
	std::string	path;
	if (!d.location->getRoot().empty() && normalizePath(d.location->getRoot() +req.getUri(), path))
	{
		d.fsPath = path;
	}
	else if (normalizePath(d.server->getRoot() + req.getUri(), path))
	{
		d.fsPath = path;
	}
	else
	{
		d.type = ACTION_ERROR;
		d.status = 400;
		d.reason = "Bad Path";
		return (d);
	}

	// CGI check

	std::string	ext, interp;
	if (hasCgi(d.location, d.relPath, ext, interp))
	{
		d.type = ACTION_CGI;
		d.cgiExt = ext;
		d.cgiInterpreter = interp;
		std::cerr << "[Router] CGI request for: " << d.fsPath << " with interpreter: " << d.cgiInterpreter << std::endl;
		return (d);
	}

	// Autoindex or static
	struct stat st; // to check file/dir
	if (::stat(d.fsPath.c_str(), &st) == 0)
	{
		// Path exists
		if (S_ISDIR(st.st_mode))
		{
			// Directory
			std::string indexFile;
			if (!d.location->getIndex().empty())
				indexFile = d.location->getIndex();
			else if (!d.server->getIndex().empty())
				indexFile = d.server->getIndex();
			
			if (!indexFile.empty())
			{
				d.fsPath += "/" + indexFile;
				d.type = ACTION_STATIC;
			}
			else if (d.location->isAutoindex())
			{
				d.type = ACTION_AUTOINDEX;
				d.autoindex = true;
				if (isMethodAllowed("DELETE", d.location, allowHeader))
				{
					d.type = ACTION_INDEXDELETE;
				}
			}
			else
			{
				d.type = ACTION_ERROR;
				d.status = 403;
				d.reason = "Forbidden";
			}
		}
		else
			d.type = ACTION_STATIC; // Regular file
	}
	else
	{
		// Path does not exist
		// std::cerr << RED << "[Router] Path does not exist: " << d.fsPath << RESET << std::endl;
		d.type = ACTION_ERROR;
		d.status = 404;
		d.reason = "Not Found";
	}

	// Upload
	if (!d.location->getUploadStore().empty() && req.getMethod() == "POST" && req.getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
	{
		d.type = ACTION_UPLOAD;
		d.uploadEnabled = true;
		d.uploadStore = d.location->getUploadStore();
	}
	else if ((req.getMethod() == "POST" && req.getBody() == "_method=DELETE" && isMethodAllowed("DELETE", d.location, allowHeader)) || (req.getMethod() == "DELETE" && isMethodAllowed("DELETE", d.location, allowHeader)))
	{
		std::cerr << "[Router] DELETE method via POST or DELETE for URI: " << req.getUri() << std::endl;
		d.type = ACTION_DELETE;
		d.uploadEnabled = false;
		d.uploadStore = d.location->getUploadStore();
	}
	else if (req.getMethod() == "POST" && req.getBody() != "_method=DELETE")
	{
		d.type = ACTION_COOKIE;
		d.uploadEnabled = false;
	}
	else if (req.getMethod() == "POST" && req.getBody() == "_method=DELETE")
	{
		d.type = ACTION_ERROR;
		d.status = 405;
		d.reason = "Method Not Allowed";
	}
	return (d);
}

const Server	*Router::selectServer( const Request &req, const ServerManager &sm )
{
	const std::vector<Server *>	&servers = sm.getServers();

	if (servers.empty())
		return (0);

	// Match by Host header
	std::string	hostHeader = req.getHeader("Host");
	std::string	hostOnly = hostHeader;
	std::string::size_type colon = hostHeader.find(':');
	if (colon != std::string::npos)
		hostOnly = hostHeader.substr(0, colon);

	// First try exact match of host:port
	for (size_t i = 0; i < servers.size(); ++i)
	{
		const std::vector<std::string> &names = servers[i]->getConfig().getServerNames();
		for (size_t j = 0; j < names.size(); ++j)
		{
			if (names[j] == hostOnly) // Exact match
				return (servers[i]);
		}
	}

	// Fallback to first server block listening on the same port
	for (size_t i = 0; i < servers.size(); ++i)
	{
		if (servers[i]->getPort() == req.getPort())
			return (servers[i]);
	}

	// Fallback to first server block
	return (servers[0]);
}

const Location	*Router::matchRoute( const std::string &uri, const Server *sb,
									std::string &mountUriOut, std::string &relPathOut )
{
	const std::vector<Location>	&locs = sb->getConfig().getLocations();
	const Location				*bestMatch = 0;
	size_t						bestLen = 0;

	// Find longest matching location prefix
	for (size_t i = 0; i < locs.size(); ++i)
	{
		const std::string	&locPath = locs[i].getPath();
		// std::cerr << "[Router] Checking location path: " << locPath << " against URI: " << uri << std::endl;
		if (uri.compare(0, locPath.size(), locPath) == 0)
		{
			// Prefix matches location path
			if (locPath.size() > bestLen)
			{
				// Longer match found
				bestLen = locPath.size();
				bestMatch = &locs[i];
			}
		}
	}

	// Set outputs
	if (bestMatch)
	{
		mountUriOut = bestMatch->getPath();
		relPathOut = uri.substr(mountUriOut.size());
		return (bestMatch);
	}
	// No match, use root
	mountUriOut = "/";
	relPathOut = uri;
	return (0);
}

// bool	Router::hasCgi( const Location *loc, const std::string &relPath,
// 					std::string &matchedExt, std::string &interp )
// {
// 	if (!loc)
// 	{
// 		return (false);
// 	}

// 	// Example: Location configured for ".py" with "/usr/bin/python"
// 	const std::vector<std::string>	&methods = loc->getMethods();
// 	if (std::find(methods.begin(), methods.end(), "POST") == methods.end())
// 		return (false); // CGI usually requires POST
	
// 	std::string::size_type dot = relPath.rfind('.');
// 	if (dot == std::string::npos)
// 		return (false); // No extension
	
// 	std::string	ext = relPath.substr(dot); // includes the dot

// 	// Check if this extension is configured for CGI
// 	if (!loc->getCgiExtension().empty() && ext == loc->getCgiExtension())
// 	{
// 		matchedExt = ext;
// 		interp = loc->getCgiPath();
// 		return (true);
// 	}
// 	return (false);
// }


// Retourne true si relPath contient un script CGI de la forme "...<ext>[ / PATH_INFO ]"
// - matchedExt : ".py" (par ex.)
// - interp     : chemin vers l'interpréteur
// - scriptEnd  : index juste après le nom du script (début de PATH_INFO)
static bool matchCgiByExt(const std::string& relPath,
						  const std::string& ext,
						  size_t& scriptEnd) {
	if (ext.empty()) return false;

	size_t pos = 0;
	while ((pos = relPath.find(ext, pos)) != std::string::npos) {
		size_t end = pos + ext.size();
		// L'extension doit être suivie d'un '/' ou de la fin de chaîne
		if (end == relPath.size() || relPath[end] == '/') {
			// Facultatif : s'assurer qu'on est bien dans un nom de fichier (pas dans un dossier nommé ".py")
			// Ici on accepte /foo/bar.py et /foo/bar.py/...
			scriptEnd = end;
			return true;
		}
		pos = end; // continuer à chercher
	}
	return false;
}

bool Router::hasCgi(const Location* loc,
					const std::string& relPath,
					std::string& matchedExt,
					std::string& interp
					/* éventuellement size_t* scriptEndOut */)
{
	if (!loc) return false;

	// ⚠️ NE PAS exiger POST ici : la validation méthode se fait ailleurs
	// (autoriser GET/POST/DELETE selon loc->getMethods())

	const std::string ext = loc->getCgiExtension();   // ex: ".py"
	if (ext.empty()) return false;

	size_t scriptEnd = std::string::npos;
	if (!matchCgiByExt(relPath, ext, scriptEnd)) return false;

	matchedExt = ext;
	interp     = loc->getCgiPath();                   // ex: "/usr/bin/python"
	// si besoin : *scriptEndOut = scriptEnd; pour construire SCRIPT_NAME / PATH_INFO
	return true;
}
