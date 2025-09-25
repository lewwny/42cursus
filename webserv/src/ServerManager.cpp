#include "../include/ServerManager.hpp"
#include <fcntl.h>

template<typename T>
static std::string toString(T n)
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

ServerManager::ServerManager(ConfigParse& config):_serverCount(config.getServerCount()) {
	_servers.reserve(_serverCount);
	for (size_t i = 0; i < _serverCount; ++i) {
		Server* server = new Server(Config(config, i));
		server->init();
		_servers.push_back(server);

		struct pollfd pfd;
		pfd.fd = server->getListenFd();
		if (pfd.fd != -1) {
			pfd.events = POLLIN;
			pfd.revents = 0;
			_pfds.push_back(pfd);
			_listenFdToServerIndex[pfd.fd] = i;
		} else {
			// std::cerr << "Warning: Server on " << server->getHost() << ":" << server->getPort() << " failed to initialize properly." << std::endl;
		}
	}
	_serverShutdown = false;
}

ServerManager::~ServerManager() {
	for (size_t i = 0; i < _servers.size(); ++i) {
		delete _servers[i];
	}
}

void ServerManager::run()
{
	while (!_serverShutdown)
	{
		int n = poll(&_pfds[0], _pfds.size(), -1);
		if ( n < 0 )
		{
			if (errno == EINTR)
				continue; // Interrupted by signal, retry
			throw std::runtime_error("Poll error: " + std::string(strerror(errno)));
		}
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if ( _pfds[i].revents & POLLIN )
			{
				bool isListenFd = false;
				for (size_t j = 0; j < _servers.size(); ++j) {
					if ( _listenFdToServerIndex.find(_pfds[i].fd) != _listenFdToServerIndex.end()) {
						acceptConnection(_pfds[i].fd);
						isListenFd = true;
						break;
					}
				}
				if (!isListenFd)
					handleRead(_pfds[i].fd);
			}
			if ( _pfds[i].revents & POLLOUT )
				handleWrite(_pfds[i].fd);	
		}
	}
	for (size_t i = 0; i < _pfds.size(); ++i) {
		if (_listenFdToServerIndex.find(_pfds[i].fd) == _listenFdToServerIndex.end()) {
			closeConnection(_pfds[i].fd);
		}
	}
	for (size_t i = 0; i < _conns.size(); ++i) {
		if (_conns[i].fd != -1) {
			close(_conns[i].fd);
		}
	}
	std::cout << "[ServerManager] Shutdown complete." << std::endl;
}


void ServerManager::acceptConnection( int fd )
{
	int clientFd = accept(fd, NULL, NULL);
	if (clientFd < 0)
	{
		std::cerr << "Accept error: " << strerror(errno) << std::endl;
		return ;
	}
	// Set client socket non-blocking to avoid blocking drain loops
	int flags = fcntl(clientFd, F_GETFL, 0);
	if (flags != -1)
		fcntl(clientFd, F_SETFL, flags | O_NONBLOCK);
	struct pollfd pfd;
	pfd.fd = clientFd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pfds.push_back(pfd);

	Connection conn;
	conn.fd = clientFd;
	conn.parser.setLimits(8192, _servers[_listenFdToServerIndex[fd]]->getConfig().getClientMaxBodySize(), 4096),
	_conns[clientFd] = conn;
	std::map<int, size_t>::iterator it = _listenFdToServerIndex.find(fd);
	if (it != _listenFdToServerIndex.end()) {
		_connFdToServerIndex[clientFd] = it->second;
	}
	std::cout << GREEN << "[Server] New connection accepted, fd: " << clientFd << RESET << std::endl;
}

void ServerManager::closeConnection(int fd)
{
	close(fd);
	_conns.erase(fd);
	_connFdToServerIndex.erase(fd);
	for (std::vector<struct pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); ++it)
	{
		if (it->fd == fd)
		{
			_pfds.erase(it);
			break ;
		}
	}
	std::cout << GREEN << "[Server] Connection closed, fd: " << fd << RESET << std::endl;
}

void	ServerManager::handleWrite( int fd )
{
	int	bytesSent;

	bytesSent = send(fd, _conns[fd].outBuffer.c_str(), _conns[fd].outBuffer.size(), 0);
	if ( bytesSent < 0 )
	{
		// if (errno == EAGAIN || errno == EWOULDBLOCK)
		// 	return; // try again later
		closeConnection(fd);
		return;
	}
	if (bytesSent == 0)
	{
		// std::cout << "[Server] Connection closed by peer, fd: " << fd << std::endl;
		closeConnection(fd);
		return;
	}
	_conns[fd].outBuffer.erase(0, bytesSent);
	if (_conns[fd].outBuffer.empty())
	{
		// If flagged to close after sending (e.g., parse error / Connection: close)
		if (_conns[fd].closeAfterSend) {
			// Half-close write side to let client read response fully, avoid RST
			shutdown(fd, SHUT_WR);
			// Switch events to POLLIN only to wait for client to close
			for (size_t i = 0; i < _pfds.size(); ++i) {
				if (_pfds[i].fd == fd) { _pfds[i].events = POLLIN; break; }
			}
			_conns[fd].closed = true; // mark so we can close once peer closes
			return;
		}
		// If the output buffer is empty, switch back to read mode
		for (long unsigned int i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].fd == fd)
			{
				_pfds[i].events = POLLIN;
				break ;
			}
		}
	}
}

static void color_status(int code, const std::string& message) {
	if (code >= 200 && code < 300)
		std::cout << GREEN << code << RESET;
	else if (code >= 300 && code < 400)
		std::cout << YELLOW << code << RESET;
	else if (code >= 400 && code < 500)
		std::cout << RED << code << RESET;
	else if (code >= 500)
		std::cout << MAGENTA << code << RESET;
	else
		std::cout << code;
	std::cout << " " << message << std::endl;
}

static bool check_session( const Request &req )
{
	std::string cookies = req.getHeader("Cookie");
	if (cookies.find("sessionid=") != std::string::npos)
		return (true);
	return (false);
}

static const std::string getSessionId( const Request &req)
{
	std::string cookies = req.getHeader("Cookie");
	size_t pos = cookies.find("sessionid=");
	if (pos == std::string::npos)
		return ("");
	pos += 10; // length of "sessionid="
	return (cookies.substr(pos, 26));
}

void	ServerManager::handleRead( int fd )
{
	char	buffer[4096];
	int		bytesRead;

	bytesRead = recv(fd, buffer, sizeof(buffer), 0);
	if (bytesRead < 0)
	{
		// // For non-blocking sockets, just return if no data ready
		// if (errno == EAGAIN || errno == EWOULDBLOCK)
		// 	return;
		closeConnection(fd);
		return;
	}
	if (bytesRead == 0)
	{
		// Peer closed; if we already sent response with closeAfterSend just cleanup
		closeConnection(fd);
		return;
	}
	Connection& con = _conns[fd];
	// If we are ignoring the rest of the request body after having sent 413, just discard
	if (con.ignoreBody) {
		return; // do nothing; wait for peer to close
	}
	Parser& parser = con.parser;
	bool done = parser.feed(std::string(buffer, bytesRead), _servers[_connFdToServerIndex[fd]]->getConfig());

	Request tmp = parser.getRequest();
	if (tmp.getError())
	{
		done = true; // Force processing of error state
		Router::Decision decision;
		decision.type = Router::ACTION_ERROR;
		decision.status = tmp.getErrorCode();
		decision.reason = tmp.getErrorMessage();
		con.outBuffer = StaticExec::makeError(decision, _servers[_connFdToServerIndex[fd]]->getConfig()).serialize();
		if (!con.outBuffer.empty()) {
			// Need to send remaining bytes asynchronously
			for (size_t i = 0; i < _pfds.size(); ++i) {
				if (_pfds[i].fd == fd) { _pfds[i].events = POLLOUT; break; }
			}
		}
		// After sending (full or partial), ignore any further request body fragments
		con.ignoreBody = true;
		con.closeAfterSend = true; // will half-close after full send in handleWrite
		parser.reset();
		return;
	}
	if (!done)
		return;

	// std::cerr << "[Parser] Request fully received, processing..." << std::endl;
	Request req = parser.getRequest();
	req.setPort(_servers[_connFdToServerIndex[fd]]->getConfig().getPort());
	if (req.getError())
	{
		// Handle request error
		// std::cerr << RED << "[Parser] Request error: " << req.getErrorMessage() << " (code " << req.getErrorCode() << ")" << RESET << std::endl;
		// _conns[fd].outBuffer = "HTTP/1.1 " + toString(req.getErrorCode()) + " " + req.getErrorMessage() + "\r\nContent-Length: 0\r\n\r\n";
		Router::Decision decision;
		decision.type = Router::ACTION_ERROR;
		decision.status = req.getErrorCode();
		decision.reason = req.getErrorMessage();
		_conns[fd].outBuffer = StaticExec::makeError(decision, _servers[_connFdToServerIndex[fd]]->getConfig()).serialize();
		// std::cout << RESET << "[METHOD]: " << req.getMethod() << " [URI]: " << req.getUri() << " [STATUS]: ";
		color_status(req.getErrorCode(), req.getErrorMessage());

	}
	else
	{
		std::string body = "You requested: " + req.getPath() + "\n";
		
		Router::Decision decision;
		decision = Router::decide(req, *this);
		Response res;
		if (req.getPath() == "/decouvrir.html" && decision.type == Router::ACTION_STATIC)
			Cookie::handleDecouvrirPage(req, res);
		else
			switch (decision.type) {
				case Router::ACTION_STATIC:
					res = StaticExec::serveStatic(decision, _servers[_connFdToServerIndex[fd]]->getConfig());
					break;
				case Router::ACTION_REDIRECT:
					std::cerr << "[Router] Redirecting to: " << decision.redirectURL << std::endl;
					res = StaticExec::makeRedirect(decision);
					break;
				case Router::ACTION_ERROR:
					res = StaticExec::makeError(decision, _servers[_connFdToServerIndex[fd]]->getConfig());
					break;
				case Router::ACTION_CGI:
					res = CGI::run(decision, req);
					break;
				case Router::ACTION_UPLOAD:
					res = Upload::save(decision, req);
					std::cout << "[Upload] File upload handled for URI: " << req.getUri() << std::endl;
					break;
				case Router::ACTION_COOKIE:
					res = Cookie::setCookie(decision, req);
					break;
				case Router::ACTION_AUTOINDEX:
					res = AutoIndex::generate(decision, req);
					break;
				case Router::ACTION_INDEXDELETE:
					res = AutoIndex::generateDelete(decision, req);
					break;
				case Router::ACTION_DELETE:
					res = Upload::deleteFile(decision, req);
					break;
				default:
					res = StaticExec::makeError(decision, _servers[_connFdToServerIndex[fd]]->getConfig());
					break;
			}
		_conns[fd].outBuffer = res.serialize();
		if (check_session(req))
		{
			try {
			std::cout << YELLOW << "For " << _servers[_connFdToServerIndex[fd]]->getConfig().getSession(getSessionId(req)) << RESET << std::endl;
			}
			catch (std::exception &e) {}
		}
		std::cout << RESET << "[METHOD]: " << req.getMethod() << " [URI]: " << req.getUri() << " [STATUS]: ";
		color_status(res.getStatusCode(), res.getStatusMessage());
	}

	// Modify state to monitor for write readiness
	for (long unsigned int i = 0; i < _pfds.size(); i++)
	{
		if (_pfds[i].fd == fd)
		{
			_pfds[i].events = POLLOUT;
			break ;
		}
	}
	parser.reset();
}

volatile sig_atomic_t ServerManager::_serverShutdown = false;
ServerManager* ServerManager::_instance = NULL;

void ServerManager::handleSignal(int signum) {
	if (signum == SIGINT) {
		if (_instance) {
			_instance->requestShutdown();
		}
	}
}
