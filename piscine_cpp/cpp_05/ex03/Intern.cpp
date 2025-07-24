/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:48:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 21:06:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

struct FormPair {
	std::string name;
	AForm* (*create)(const std::string&);
};

Intern::Intern() {}

Intern::Intern(const Intern& src) {
	(void)src;
}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern& src) {
	(void)src;
	return *this;
}

AForm* createShrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* createRobotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* createPardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm*	Intern::makeForm(const std::string& nameform, const std::string& target) const
{
	FormPair forms[3] = {
		{"shrubbery creation", createShrubbery},
		{"robotomy request", createRobotomy},
		{"presidential pardon", createPardon}
	};
	
	for (int i = 0; i < 3 ; ++i)
	{
		if (nameform == forms[i].name)
		{
			std::cout << "Intern creates " << nameform << std::endl;
			return forms[i].create(target);
		}
	}
	std::cerr << "Error form name -- " << nameform << " -- doesn't exist." << std::endl;
	return NULL;
}