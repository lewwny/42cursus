
#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>
#include <poll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "Request.hpp"
#include "Response.hpp"
#include "Parser.hpp"
#include "ConfigParse.hpp"
#include "Config.hpp"
#include "Router.hpp"
#include "Cookie.hpp"
#include "AutoIndex.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define MAGENTA "\033[1;35m"

class Server
{
public:
	Server(const Config &config );
	~Server( void );

	void init( void ); // create listening socket
	int getListenFd() const { return _listenFd; }
	const Config& getConfig() const { return _config; }
	Config& getConfig() { return _config; }
	const std::string& getHost() const { return _host; }
	int getPort() const { return _port; }
private:
	int _listenFd;
	Config _config;
	int _port;
	std::string _host;
	Server(); // prevent default constructor
	Server(const Server &); // prevent copy constructor
	Server &operator=(const Server &); // prevent assignment operator
};

#endif
