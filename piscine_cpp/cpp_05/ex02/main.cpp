/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:30:59 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 19:38:26 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::srand(std::time(NULL)); // initialise le hasard

	std::cout << CYAN << "=== SHRUBBERY : signature & exécution OK ===" << RESET << std::endl;
	try {
		Bureaucrat bob("Bob", 1);
		ShrubberyCreationForm form("garden");
		bob.signForm(form);
		bob.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : exécution sans signature ===" << RESET << std::endl;
	try {
		Bureaucrat alice("Alice", 1);
		ShrubberyCreationForm form("forest");
		alice.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : signature refusée (grade bas) ===" << RESET << std::endl;
	try {
		Bureaucrat low("Low", 150);
		ShrubberyCreationForm form("city");
		low.signForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : exécution refusée (grade bas) ===" << RESET << std::endl;
	try {
		Bureaucrat signer("Signer", 1);
		Bureaucrat executor("Executor", 150);
		ShrubberyCreationForm form("park");
		signer.signForm(form);
		executor.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : double exécution ===" << RESET << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm form("yard");
		boss.signForm(form);
		boss.executeForm(form);
		boss.executeForm(form); // autorisé, recrée le fichier
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== ROBOTOMY : success ou fail ===" << RESET << std::endl;
	try {
		Bureaucrat roboto("RoboGuy", 1);
		RobotomyRequestForm form("marvin");
		roboto.signForm(form);
		for (int i = 0; i < 5; ++i)
			roboto.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== ROBOTOMY : exécution refusée sans signature ===" << RESET << std::endl;
	try {
		Bureaucrat exec("Exec", 1);
		RobotomyRequestForm form("targetX");
		exec.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : exécution OK ===" << RESET << std::endl;
	try {
		Bureaucrat pres("Prez", 1);
		PresidentialPardonForm form("Trillian");
		pres.signForm(form);
		pres.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : refusé (pas signé) ===" << RESET << std::endl;
	try {
		Bureaucrat exec("Exec", 1);
		PresidentialPardonForm form("Ford");
		exec.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : refusé (grade trop bas) ===" << RESET << std::endl;
	try {
		Bureaucrat low("LowGuy", 150);
		PresidentialPardonForm form("Arthur");
		low.signForm(form);
		low.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}