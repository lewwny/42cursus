/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:30:59 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 20:59:03 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define CYAN  "\033[1;36m"
#define RESET "\033[0m"

int main() {
	std::cout << CYAN << "=== INTERN TEST : valid forms ===" << RESET << std::endl;
	Intern someIntern;

	AForm* shrub = someIntern.makeForm("shrubbery creation", "garden");
	AForm* robot = someIntern.makeForm("robotomy request", "marvin");
	AForm* pardon = someIntern.makeForm("presidential pardon", "Trillian");

	std::cout << CYAN << "\n=== SIGN & EXECUTE each ===" << RESET << std::endl;
	try {
		Bureaucrat b("Boss", 1);

		b.signForm(*shrub);
		b.executeForm(*shrub);

		b.signForm(*robot);
		b.executeForm(*robot);

		b.signForm(*pardon);
		b.executeForm(*pardon);
	} catch (const std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== INTERN TEST : invalid form ===" << RESET << std::endl;
	AForm* invalid = someIntern.makeForm("coffee maker", "kitchen");
	if (!invalid)
		std::cout << RED << "Form creation failed as expected." << RESET << std::endl;

	// Nettoyage mémoire
	delete shrub;
	delete robot;
	delete pardon;
	delete invalid; // nullptr safe

	return 0;
}