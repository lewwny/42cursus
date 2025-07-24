/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:30:59 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 18:33:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::cout << CYAN << "===== CONSTRUCTION DE FormULAIRE VALIDE =====" << RESET << std::endl;
	try {
		Form FormA("FormA", 50, 25);
		std::cout << GREEN << FormA << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION AVEC GRADE TROP BAS =====" << RESET << std::endl;
	try {
		Form FormB("FormB", 151, 25);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION AVEC GRADE TROP HAUT =====" << RESET << std::endl;
	try {
		Form FormC("FormC", 10, 0);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== SIGNATURE RÉUSSIE =====" << RESET << std::endl;
	try {
		Bureaucrat alice("Alice", 30);
		Form FormD("FormD", 50, 10);
		std::cout << alice << std::endl;
		std::cout << FormD << std::endl;
		alice.signForm(FormD);
		std::cout << GREEN << FormD << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== SIGNATURE ÉCHOUÉE (GRADE TROP BAS) =====" << RESET << std::endl;
	try {
		Bureaucrat bob("Bob", 120);
		Form FormE("FormE", 100, 100);
		std::cout << bob << std::endl;
		std::cout << FormE << std::endl;
		bob.signForm(FormE);
		std::cout << GREEN << FormE << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== SIGNATURE MULTIPLE =====" << RESET << std::endl;
	try {
		Bureaucrat claire("Claire", 10);
		Form FormF("FormF", 20, 5);
		std::cout << claire << std::endl;
		std::cout << FormF << std::endl;
		claire.signForm(FormF);
		claire.signForm(FormF);  // déjà signée
		std::cout << GREEN << FormF << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}