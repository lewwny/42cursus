#ifndef COOKIE_HPP
#define COOKIE_HPP

#include "Server.hpp"
#include "ServerManager.hpp"

class Cookie
{
public:
	static Response setCookie(const Router::Decision& d, const Request& req);
	static void handleDecouvrirPage(const Request &req, Response &res);
};

#endif