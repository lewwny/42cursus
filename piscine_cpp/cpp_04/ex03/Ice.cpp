/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:40:19 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:02:35 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {
	// std::cout << "\033[32mIce default constructor called\033[0m" << std::endl;
}

Ice::Ice(const Ice& other) : AMateria(other._type) {
	// std::cout << "\033[32mIce copy constructor called\033[0m" << std::endl;
}

Ice& Ice::operator=(const Ice& other) {
	if (this != &other) {
		_type = other._type;
	}
	// std::cout << "\033[32mIce assignment operator called\033[0m" << std::endl;
	return *this;
}

Ice::~Ice() {
	// std::cout << "\033[31mIce destructor called\033[0m" << std::endl;
}

AMateria* Ice::clone() const {
	// std::cout << "\033[32mIce clone called\033[0m" << std::endl;
	return new Ice(*this);
}

void Ice::use(ICharacter& target) {
	std::cout << "\033[34m* shoots an ice bolt at " << target.getName() << " *\033[0m" << std::endl;
}