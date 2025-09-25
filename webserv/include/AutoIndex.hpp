#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP

#include "Server.hpp"
#include "StaticExec.hpp"

class AutoIndex
{
public:
	static Response generate(const Router::Decision &d, const Request &req);
	static Response generateDelete(const Router::Decision &d, const Request &req);
};

#endif