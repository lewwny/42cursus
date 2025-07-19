/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:46:41 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:02:23 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {
	// std::cout << "\033[32mCure default constructor called\033[0m" << std::endl;
}

Cure::Cure(const Cure& other) : AMateria(other._type) {
	// std::cout << "\033[32mCure copy constructor called\033[0m" << std::endl;
}

Cure& Cure::operator=(const Cure& other) {
	if (this != &other) {
		_type = other._type;
	}
	// std::cout << "\033[32mCure assignment operator called\033[0m" << std::endl;
	return *this;
}

Cure::~Cure() {
	// std::cout << "\033[31mCure destructor called\033[0m" << std::endl;
}

AMateria* Cure::clone() const {
	// std::cout << "\033[32mCure clone called\033[0m" << std::endl;
	return new Cure(*this);
}

void Cure::use(ICharacter& target) {
	std::cout << "\033[34m* heals " << target.getName() << "'s wounds *\033[0m" << std::endl;
}