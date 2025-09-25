#include "../include/Cookie.hpp"

template<typename T>
static std::string toString(T n)
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

Response Cookie::setCookie(const Router::Decision& d, const Request& req)
{
	Response res;
	
	(void)d;
	if (req.getMethod() != "POST")
	{
		Router::Decision tmp = d;
		tmp.reason = "Method Not Allowed";
		res = StaticExec::makeError(tmp, *d.server);
		return ( res );
	}
	else if (req.getHeader("Content-Type").find("application/x-www-form-urlencoded") == std::string::npos)
	{
		Router::Decision tmp = d;
		tmp.reason = "Unsupported Media Type";
		res = StaticExec::makeError(tmp, *d.server);
		return ( res );
	}
	std::string cookieBody = req.getBody();
	std::string cookieName, cookieValue;
	size_t eqPos = cookieBody.find('=');
	if (eqPos == std::string::npos || eqPos == 0 || eqPos == cookieBody.size() - 1)
	{
		res.setStatus(400, "Bad Request");
		const std::string body = " Body must contain cookie in the format name=value.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		Router::Decision tmp = d;
		tmp.reason = "Malformed cookie data";
		res = StaticExec::makeError(tmp, *d.server);
		return ( res );
	}
	res.addSetCookie(cookieBody);
	res.setStatus(204, "No-Content");
	res.addSecurityHeaders();
	std::cout << "[Cookie] Set-Cookie: " << cookieBody << std::endl;
	return res;
}

static std::string loadFile(const std::string &path) {
	std::ifstream f(path.c_str());
	std::ostringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

static std::string getCookieValue(const std::string &cookieHeader, const std::string &name) {
	std::string search = name + "=";
	size_t pos = cookieHeader.find(search);
	if (pos == std::string::npos) return "";
	pos += search.size();
	size_t end = cookieHeader.find(";", pos);
	return cookieHeader.substr(pos, end - pos);
}

static bool isAllowed(const std::string& s) {
	static const char* A[] = {"Belier","Taureau","Gemeaux","Cancer","Lion","Vierge","Balance","Scorpion","Sagittaire","Capricorne","Verseau","Poissons"};
	for (size_t i=0;i<12;i++)
		if (s==A[i]) return true;
	return false;
}

void Cookie::handleDecouvrirPage(const Request &req, Response &res) {
	std::string html = loadFile("www/decouvrir.html");

	std::string cookieHeader = req.getHeader("Cookie");
	std::string signe = getCookieValue(cookieHeader, "signe");

	std::string extra;
	if (!signe.empty() && isAllowed(signe)) {
		std::string block =
			"<div id=\"quick-horoscope\" style=\"text-align:center;margin-top:1rem;\">"
			"<form action=\"/cgi-bin/py/test.py\" method=\"POST\" class=\"quick-horo-form\">"
			"<input type=\"hidden\" name=\"signe\" value=\"" + signe + "\">"
			"<button type=\"submit\" class=\"submit-btn\">Générer mon Horoscope pour " + signe + "</button>"
			"</form></div>";
		size_t pos = html.find("</form>");
		if (pos != std::string::npos) html.insert(pos + 7, block);
		else {
			size_t end = html.find("</body>");
			if (end != std::string::npos) html.insert(end, block);
		}
	}

	res.setStatus(200, "OK");
	res.setHeader("Content-Type", "text/html; charset=utf-8");
	res.setHeader("Content-Length", toString(html.size()));
	res.setBody(html);
}
