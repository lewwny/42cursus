/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:28:59 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:01:28 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria() : _type("default")
{
	// std::cout << "\033[32mAMateria default constructor called\033[0m" << std::endl;
}

AMateria::AMateria(std::string const & type) : _type(type)
{
	// std::cout << "\033[32mAMateria constructor called for type: "
	// << _type << "\033[0m" << std::endl;
}

AMateria::AMateria(const AMateria& other) : _type(other._type)
{
	// std::cout << "\033[34mAMateria copy constructor called for type: "
	// << _type << "\033[0m" << std::endl;
}

AMateria::~AMateria()
{
	// std::cout << "\033[31mAMateria destructor called for type: "
	// << _type << "\033[0m" << std::endl;
}

std::string const & AMateria::getType() const
{
	return _type;
}

AMateria& AMateria::operator=(const AMateria& other)
{
	if (this != &other)
	{
		_type = other._type;
		// std::cout << "\033[34mAMateria assignment operator called for type: "
		// << _type << "\033[0m" << std::endl;
	}
	return *this;
}

void AMateria::use(ICharacter& target)
{
	std::cout << "\033[34m* uses " << _type << " on " << target.getName() << " *\033[0m" << std::endl;
}