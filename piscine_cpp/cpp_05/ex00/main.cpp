/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:30:59 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 15:03:32 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::cout << CYAN << "===== CONSTRUCTION VALIDE =====" << RESET << std::endl;
	try {
		Bureaucrat a("Alice", 42);
		std::cout << GREEN << a << RESET << std::endl;

		a.incrementGrade();
		std::cout << "Après increment: " << GREEN << a << RESET << std::endl;

		a.decrementGrade();
		std::cout << "Après decrement: " << GREEN << a << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION GRADE TROP HAUT =====" << RESET << std::endl;
	try {
		Bureaucrat b("Bob", 0);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION GRADE TROP BAS =====" << RESET << std::endl;
	try {
		Bureaucrat c("Charlie", 200);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== INCREMENT AU MAX =====" << RESET << std::endl;
	try {
		Bureaucrat d("Diane", 1);
		std::cout << GREEN << d << RESET << std::endl;
		d.incrementGrade();
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== DECREMENT AU MIN =====" << RESET << std::endl;
	try {
		Bureaucrat e("Edward", 150);
		std::cout << GREEN << e << RESET << std::endl;
		e.decrementGrade();
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== TEST COPIE & ASSIGNATION =====" << RESET << std::endl;
	try {
		Bureaucrat f("Frank", 100);
		Bureaucrat g = f;
		Bureaucrat h("Harry", 50);
		h = f;

		std::cout << "f: " << GREEN << f << RESET << std::endl;
		std::cout << "g (copie de f): " << GREEN << g << RESET << std::endl;
		std::cout << "h (assigné à f): " << GREEN << h << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}