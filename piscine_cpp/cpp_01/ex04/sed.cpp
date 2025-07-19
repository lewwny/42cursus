/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:43:41 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/24 12:00:15 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

Sed::Sed(const std::string& filename, const std::string& s1, const std::string& s2)
	: _filename(filename),
	_s1(s1),
	_s2(s2)
{
	process();
}

Sed::~Sed()
{}

std::string	Sed::_readFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << filename << " can't be open." << std::endl;
		exit(1);
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return (buffer.str());
}

void	Sed::_writeFile(const std::string& filename, const std::string& content)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cerr << filename << " can't be open." << std::endl;
		exit(1);
	}
	file << content;
	file.close();
}

void	Sed::process(void)
{
	std::string	buffer = Sed::_readFile(_filename);
	std::string result = "";
	std::size_t pos = 0;
	std::size_t	find = buffer.find(_s1);
	while (find != std::string::npos)
	{
		result += buffer.substr(pos, find - pos);
		result += _s2;
		pos = find + _s1.length();
		find = buffer.find(_s1, pos);
	}
	result += buffer.substr(pos);
	_writeFile(_filename+".replace", result);
}