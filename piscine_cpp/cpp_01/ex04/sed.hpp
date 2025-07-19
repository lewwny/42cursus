/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:38:41 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/24 11:55:09 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class	Sed
{
public:
	Sed(const std::string& filename, const std::string& s1, const std::string& s2);
	~Sed();
	void	process(void);
private:
	const std::string& _filename;
	const std::string& _s1;
	const std::string& _s2;
	
	std::string	_readFile(const std::string& filename);
	void	_writeFile(const std::string& filename, const std::string& content);
};