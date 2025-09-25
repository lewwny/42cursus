/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:28:04 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/09/15 13:41:16 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Upload.hpp"
#include "../include/StaticExec.hpp"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// C++98 compatible toString helper  
template<typename T>
static std::string toString(T value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

bool Upload::isDir( const std::string& path )
{
	struct stat info;
	//truncate the first / if there is a /
	if (path[0] == '/' && path.size() > 1)
	{
		std::string tmp = path.substr(1);
		return ( Upload::isDir(tmp) );
	}
	if (stat(path.c_str(), &info) != 0)
		return ( false );
	return ( S_ISDIR(info.st_mode) );
}

bool Upload::getUploadDir( const std::string& dir )
{
	if (dir.empty())
		return ( false );
	if (Upload::isDir(dir))
		return ( true );
	if (mkdir(dir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
		return ( false );
	return ( true );
}

bool Upload::invalidFilename( const std::string& name )
{
	// Vérifie si le nom de fichier est invalide (!= de find(".") et "..", car si ex.txt -> valide)
	if (name.empty() || name == "." || name == "..")
		return ( true );
	if (name.find('/') != std::string::npos || name.find('\\') != std::string::npos)
		return ( true );
	std::string invalidChars = "<>:\"|?*"; // Caractères interdits dans les noms de fichiers
	for (size_t i = 0; i < name.size(); ++i)
	{
		if (invalidChars.find(name[i]) != std::string::npos)
			return ( true );
	}
	return ( false );
}

std::string Upload::joinPath( const std::string& dir, const std::string& name )
{
	if (dir.empty())
		return ( name );
	if (dir[dir.size() - 1] == '/') 
		return ( dir + name );
	return ( dir + "/" + name );
}

/*
	utile quand le serveur reçoit plusieurs fichiers et que le serveur ne fournit pas de nom de fichier (ex: d.)
	ex : upload_1693651234567890.bin
*/
std::string Upload::generateUniqueFilename( void )
{
	std::time_t now = std::time(0);
	int randomNum = std::rand();
	std::ostringstream oss;
	oss << "_upload" << now << "_" << randomNum << ".bin";
	return ( oss.str() );
}
/*
// Purpose of this function: Save the body of the request (POST) into a file in the directory specified by d.uploadStore.
// The file name can be uniquely generated (e.g., using a timestamp or a UUID).
// If the save is successful, return a 201 Created response.
// If an error occurs (e.g., the directory does not exist), return a 500 Internal Server Error response.
//         std::string uploadStore;      // target directory for uploads
Response Upload::save(const Router::Decision& d, const Request& req)
{
	Response			res;
	std::string		uploadDir = d.uploadStore; // Contient le répertoire de stockage des uploads

	if (uploadDir[0] == '/' && uploadDir.size() > 1) // Si le chemin commence par /, on le tronque
		uploadDir = uploadDir.substr(1);
	if (uploadDir.empty() || !Upload::isDir(uploadDir)) // condition si le répertoire n'existe pas ou n'est pas configuré
	{
		res.setStatus(403, "Forbidden");
		const std::string body = " Upload directory is not configured or does not exist.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return ( res );
	}
	if (!getUploadDir(uploadDir)) // condition pour créer le répertoire s'il n'existe pas
	{
		res.setStatus(500, "Internal Server Error");
		const std::string body = " Failed to create upload directory.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8"); // pas sur si utile
		res.addSecurityHeaders();
		return ( res );
	}
	const std::string &data = req.getBody(); // recupere le contenu de la requête POST ( Si un client envoie une image, data contiendra tous les bytes de cette image
	if (data.empty())
	{
		res.setStatus(400, "Bad Request");
		const std::string body = " Request body is empty.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return ( res );
	}
	std::string filename = generateUniqueFilename(); // génère un nom de fichier unique
	std::string filePath = joinPath(uploadDir, filename); // crée le chemin complet du fichier en joignant le répertoire et le nom du fichier
	if (invalidFilename(filename)){
		res.setStatus(500, "Internal Server Error");
		const std::string body = " Generated filename is invalid.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return ( res );
	}
	std::ofstream ofs(filePath.c_str(), std::ios::binary); // Ouvre le fichier en mode binaire (important pour les fichiers non-texte : PDF , images, etc.)
	if (!ofs)
	{
		res.setStatus(500, "Internal Server Error");
		const std::string body = " Failed to open file for writing.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return ( res );
	}
	// Recevoir un corps de requête (POST) et l’enregistrer tel quel sur disque.
	ofs.write(data.data(), static_cast<std::streamsize>(data.size())); // Écrit toutes les donnees brutes, même les null bytes (\0) + convertit en type attendu par write
	if (ofs.fail())
	{
		res.setStatus(500, "Internal Server Error");
		const std::string body = " Failed to write data to file.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return ( res );
	}
	ofs.close();
	res.setStatus(204, "Created");
	res.setHeader("Content-Length", "0");
	res.setHeader("Content-Type", "text/plain; charset=utf-8");
	res.addSecurityHeaders();
	return ( res );
}*/

// Save the body of the request (POST) into a file in the directory specified by d.uploadStore.
// Returns a 201 Created response if successful, or an error response otherwise.
Response Upload::save(const Router::Decision& d, const Request& req)
{
	Response res;
	std::string uploadDir = d.uploadStore;

	// Validate the upload directory path
	if (uploadDir[0] == '/' && uploadDir.size() > 1)
		uploadDir = uploadDir.substr(1);
	if (uploadDir.empty() || !Upload::isDir(uploadDir)) {
		res.setStatus(403, "Forbidden");
		const std::string body = "Upload directory is not configured or does not exist.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return res;
	}
	if (!getUploadDir(uploadDir)) {
		res.setStatus(500, "Internal Server Error");
		const std::string body = "Failed to create upload directory.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return res;
	}

	// Check if request body is empty
	const std::string &data = req.getBody();
	if (data.empty()) {
		res.setStatus(400, "Bad Request");
		const std::string body = "Request body is empty.\n";
		res.setBody(body);
		res.setHeader("Content-Length", toString(body.size()));
		res.setHeader("Content-Type", "text/plain; charset=utf-8");
		res.addSecurityHeaders();
		return res;
	}

	size_t maxSize = d.location->getClientMaxBodySize() > 0 
					? d.location->getClientMaxBodySize() 
					: d.server->getClientMaxBodySize();
	if (data.size() > maxSize) {
		Router::Decision tmp = d;
		tmp.status = 413;
		tmp.reason = "Payload Too Large";
		return StaticExec::makeError(tmp, *d.server);
	}

	std::string filename = generateUniqueFilename();
	std::string filePath = joinPath(uploadDir, filename);

	// Validate generated filename
	if (invalidFilename(filename)) {
		Router::Decision tmp = d;
		tmp.status = 500;
		tmp.reason = "Internal Server Error";
		return StaticExec::makeError(tmp, *d.server);
	}

	std::ofstream ofs(filePath.c_str(), std::ios::binary);
	if (!ofs) {
		Router::Decision tmp = d;
		tmp.status = 500;
		tmp.reason = "Internal Server Error";
		return StaticExec::makeError(tmp, *d.server);
	}

	// Write data in chunks to save memory
	const size_t CHUNK_SIZE = 8192; // 8KB
	const char* dataPtr = data.data();
	size_t remaining = data.size();
	size_t written = 0;

	while (remaining > 0) {
		size_t toWrite = std::min(CHUNK_SIZE, remaining);
		ofs.write(dataPtr + written, static_cast<std::streamsize>(toWrite));
		if (ofs.fail()) {
			ofs.close();
			// Remove file if write fails
			std::remove(filePath.c_str());
			Router::Decision tmp = d;
			tmp.status = 500;
			tmp.reason = "Internal Server Error";
			return StaticExec::makeError(tmp, *d.server);
		}
		written += toWrite;
		remaining -= toWrite;
	}

	ofs.close();

	// Return success response with 204 No Content
	res.setStatus(204, "No Content");
	res.setHeader("Content-Length", "0");
	res.addSecurityHeaders();
	return res;
}

Response Upload::deleteFile(const Router::Decision& d, const Request& req)
{
	Response res;
	std::string uploadDir = d.uploadStore;

	// Validate the upload directory path
	// if (uploadDir[0] == '/' && uploadDir.size() > 1)
	// 	uploadDir = uploadDir.substr(1);
	// if (uploadDir.empty() || !Upload::isDir(uploadDir)) {
	// 	Router::Decision errorDecision;
	// 	errorDecision.status = 403;
	// 	errorDecision.reason = "Forbidden";
	// 	return StaticExec::makeError(errorDecision, *d.server);
	// }

	std::string filename = req.getPath();
	if (filename.empty() || filename[0] == '/')
		filename = filename.substr(1); // Remove leading slash if present

	std::string filePath = d.fsPath;

	if (std::remove(filePath.c_str()) != 0) {
		Router::Decision errorDecision;
		errorDecision.status = 404;
		errorDecision.reason = "Not Found";
		return StaticExec::makeError(errorDecision, *d.server);
	}
	std::cerr << "[Upload] File deleted successfully: " << filePath << std::endl;
	res.setStatus(204, "No Content");
	res.setHeader("Content-Length", "0");
	res.addSecurityHeaders();
	return res;
}