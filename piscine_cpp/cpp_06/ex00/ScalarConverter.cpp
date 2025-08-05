/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:14:09 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/08/01 14:39:53 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

static bool	isFloat(const std::string& s)
{
	if (s == "-inff" || s == "+inff" || s == "nanf")
		return true;
	if (s.empty() || s[s.size() - 1] != 'f')
		return false;
	std::string nb = s.substr(0, s.length() - 1);
	bool	hasdot = false;
	bool	hasdigit = false;
	size_t	i = 0;
	
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	for (; i < nb.length() ; i++)
	{
		if (std::isdigit(nb[i]))
			hasdigit = true;
		else if (nb[i] == '.' && !hasdot)
			hasdot = true;
		else
			return false;
	}
	return hasdigit && hasdot;	
}

static bool	isDouble(const std::string& s)
{
	if (s == "-inf" || s == "+inf" || s == "nan" || s == "inf")
		return true;
	if (s.empty() || s[s.size() - 1] == 'f')
		return false;
	bool	hasdot = false;
	bool	hasdigit = false;
	size_t	i = 0;
	
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (; i < s.length() ; i++)
	{
		if (std::isdigit(s[i]))
			hasdigit = true;
		else if (s[i] == '.' && !hasdot)
			hasdot = true;
		else
			return false;
	}
	return hasdigit && hasdot;
}

static bool	isChar(const std::string& s)
{
	if (!s.empty() && s.length() == 1 && std::isprint(s[0]) && !std::isdigit(s[0]))
		return true;
	return false;
}

static bool	isInt(const std::string& s)
{
	if (s.empty())
		return false;
	size_t	i = 0;
	bool hasdigit = false;
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (; i < s.length() ; i++)
	{
		if (std::isdigit(s[i]))
			hasdigit = true;
		else
			return false;
	}
	return hasdigit;
}

static void	display(int nb, float f, double d, char c)
{
	std::string ff = "";
	std::string dd = "";
	if (c == -1)
		std::cout << "char: Impossible" << std::endl;
	else if (!std::isprint(c))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << c << std::endl;
	if (d > 2147483647 || d < -2147483648)
		std::cout << "int: Out of range" << std::endl;
	else if (std::isnan(d) || std::isnan(f))
		std::cout << "int: Impossible" << std::endl;
	else
		std::cout << "int: " << nb << std::endl;
	if (f > 1.175494e-38 && f < 3.402823e+38 && std::fmod(f, 1.0f) == 0.0f)
		ff = ".0";
	if (d > 1.7976931348623157e-308 && d < 1.7976931348623157e+308 && std::fmod(d, 1.0) == 0.0)
		dd = ".0";
	std::cout << "float: " << f << ff << "f" << std::endl;
	std::cout << "double: " << d << dd << std::endl;
	errno = 0;
}

static void	displayint(const std::string& literal)
{
	bool	out = false;
	int		nb = 0;
	float	f;
	double	d;
	bool	err = false;
	long tmp = std::strtol(literal.c_str(), NULL, 10);
	if (errno == ERANGE || tmp < INT_MIN || tmp > INT_MAX)
		err = true;
	if (!err)
	{
		nb = tmp;
		f = static_cast<float>(nb);
		d = static_cast<double>(nb);
	}
	else
	{
		d = std::strtod(literal.c_str(), NULL);
		f = static_cast<float>(d);
		out = true;
	}
	char c = -1;
	if (!out && d < 128 && d >= 0)
		c = static_cast<char>(d);
	display(nb, f, d, c);
	
}

static void	displaychar(const std::string& literal)
{
	char c = literal[0];
	int nb = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);
	display(nb, f, d, c);
}

static void displayfloat(const std::string& literal)
{
	int nb;
	float f;
	double d;
	float tmp = std::strtof(literal.c_str(), NULL);
	if (errno == ERANGE)
	{
		d = std::strtod(literal.c_str(), NULL);
		f = static_cast<float>(d);
		nb = static_cast<int>(d);
	}
	else
	{
		f = tmp;
		d = static_cast<double>(f);
		nb = static_cast<int>(f);
	}
	char c = -1;
	if (d < 128 && d >= 0)
		c = static_cast<char>(d);
	display(nb, f, d, c);
}

static void displaydouble(const std::string& literal)
{
	int nb;
	float f;
	double d;
	
	d = std::strtod(literal.c_str(), NULL);
	if (errno == ERANGE)
	{
		f = static_cast<float>(d);
		nb = static_cast<int>(d);
	}
	else
	{
		f = static_cast<float>(d);
		nb = static_cast<int>(d);
	}
	char c = -1;
	if (d < 128 && d >= 0)
		c = static_cast<char>(d);
	display(nb, f, d, c);
}

static void displayimpossible()
{
	std::cout << "char: Impossible" << std::endl;
	std::cout << "int: Impossible" << std::endl;
	std::cout << "float: Impossible" << std::endl;
	std::cout << "double: Impossible" << std::endl;
}

void	ScalarConverter::convert(const std::string& literal)
{
	if (isInt(literal))
		displayint(literal);
	else if (isFloat(literal))
		displayfloat(literal);
	else if (isDouble(literal))
		displaydouble(literal);
	else if (isChar(literal))
		displaychar(literal);
	else
		displayimpossible();
}