#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "Config.hpp"
#include "Server.hpp"
#include "ConfigParse.hpp"
#include "CGI.hpp"
#include "StaticExec.hpp"
#include "Upload.hpp"

struct Connection {
	int fd;
	// std::string inBuffer;
	Parser parser;
	std::string outBuffer;
	bool closed;
	bool ignoreBody;      // when true, discard incoming data without parsing
	bool closeAfterSend;  // half-close after sending response, wait peer close
	Connection() : fd(-1), closed(false)
		, ignoreBody(false), closeAfterSend(false)
	{}
};

class ServerManager {
public:
	ServerManager(ConfigParse& config);
	~ServerManager();

	void run();

	static void handleSignal(int signum);
	static void setInstance(ServerManager* instance) { _instance = instance; }
	void requestShutdown() { _serverShutdown = true; }
	const std::vector<Server*>& getServers() const { return _servers; }
private:
	std::vector<Server*> _servers;
	size_t _serverCount;

	std::vector<struct pollfd> _pfds;
	std::map<int, Connection> _conns; // map of fd to Connection
	std::map<int, size_t> _listenFdToServerIndex; // map of fd to server index
	std::map<int, size_t> _connFdToServerIndex; // map of connection fd to server index
	static volatile sig_atomic_t _serverShutdown;
	static ServerManager* _instance;
	void acceptConnection(int fd);
	void handleRead(int fd);
	void handleWrite(int fd);
	void closeConnection(int fd);
};

#endif
