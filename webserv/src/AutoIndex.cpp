#include "../include/AutoIndex.hpp"

template<typename T>
static std::string toString(T n)
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

Response AutoIndex::generate( const Router::Decision &d, const Request &req )
{
	std::string				body;
	std::string				uri = d.relPath;
	DIR						*dir;
	struct dirent			*entry;
	struct stat				info;
	std::string				fullPath = d.fsPath;

	// Ensure the path ends with a slash for directory listing
	(void)req;
	if (fullPath.empty() || fullPath[fullPath.size() - 1] != '/')
		fullPath += '/';
	if (uri.empty() || uri[uri.size() - 1] != '/')
		uri += '/';

	dir = opendir(fullPath.c_str());
	if (!dir)
	{
		Router::Decision errorDecision;
		errorDecision.status = 500;
		errorDecision.reason = "Internal Server Error";
		return StaticExec::makeError(errorDecision, *d.server);
	}

	body += "<html><head><title>Index of " + uri + "</title></head><body>";
	body += "<h1>Index of " + uri + "</h1><hr><pre>";

	while ((entry = readdir(dir)) != NULL)
	{
		std::string name = entry->d_name;

		// Skip hidden files and parent directory link
		if (name == "." || name == "..")
			continue;

		if (name.size() < 5 || name.substr(name.size() - 5) != ".html")
			continue;
		std::string entryPath = fullPath + name;
		if (stat(entryPath.c_str(), &info) == 0)
		{
			if (S_ISDIR(info.st_mode))
				name += "/";
			else if (S_ISLNK(info.st_mode))
				name += "@";
		}

		body += "<a href=\"" + uri + name + "\">" + name + "</a>\n";
	}

	body += "</pre><hr></body></html>";
	closedir(dir);

	Response res;
	res.setStatus(200, "OK");
	res.setHeader("Content-Type", "text/html");
	res.setHeader("Content-Length", toString(body.size()));
	res.setBody(body);
	if (d.keepAlive)
		res.setHeader("Connection", "keep-alive");
	else
		res.setHeader("Connection", "close");
	return res;
}

Response AutoIndex::generateDelete( const Router::Decision &d, const Request &req )
{
	std::string				body;
	std::string				uri = d.mountUri;
	DIR						*dir;
	struct dirent			*entry;
	struct stat				info;
	std::string				fullPath = d.fsPath;

	// Ensure the path ends with a slash for directory listing
	(void)req;
	if (fullPath.empty() || fullPath[fullPath.size() - 1] != '/')
		fullPath += '/';
	if (uri.empty() || uri[uri.size() - 1] != '/')
		uri += '/';

	dir = opendir(fullPath.c_str());
	if (!dir)
	{
		Router::Decision errorDecision;
		errorDecision.status = 500;
		errorDecision.reason = "Internal Server Error";
		return StaticExec::makeError(errorDecision, *d.server);
	}

	body += "<html><head><title>Index of " + uri + "</title></head><body>";
	body += "<h1>Index of " + uri + "</h1><hr><pre>";

	while ((entry = readdir(dir)) != NULL)
	{
		std::string name = entry->d_name;

		// Skip hidden files and parent directory link
		if (name == "." || name == "..")
			continue;

		std::string entryPath = fullPath + name;
		if (stat(entryPath.c_str(), &info) == 0)
		{
			if (S_ISDIR(info.st_mode))
				name += "/";
			else if (S_ISLNK(info.st_mode))
				name += "@";
		}

		body += "<a href=\"" + uri + name + "\">" + name + "</a>\n";
		body += "<form method=\"POST\" action=\"" + uri + name + "\">";
		body += "<input type=\"hidden\" name=\"_method\" value=\"DELETE\">";
		body += "<input type=\"submit\" value=\"Delete\">";
		body += "</form>\n";
	}

	body += "</pre><hr></body></html>";
	closedir(dir);

	Response res;
	res.setStatus(200, "OK");
	res.setHeader("Content-Type", "text/html");
	res.setHeader("Content-Length", toString(body.size()));
	res.setBody(body);
	if (d.keepAlive)
		res.setHeader("Connection", "keep-alive");
	else
		res.setHeader("Connection", "close");
	return res;
}
