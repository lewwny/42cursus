/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:24:22 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/13 21:31:33 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

void test(Point const& a, Point const& b, Point const& c, Point const& p)
{
	std::cout << CYAN << "Test du point (" << p.getX() << ", " << p.getY() << ") : ";
	if (bsp(a, b, c, p))
		std::cout << GREEN << CHECKMARK << " À l'intérieur du triangle" << RESET << std::endl;
	else
		std::cout << RED << CROSS << " À l'extérieur du triangle" << RESET << std::endl;
}

int main(void)
{
	std::cout << BOLD << "=== Test de la fonction bsp ===" << RESET << std::endl;

	Point a(0, 0);
	Point b(10, 0);
	Point c(5, 10);

	std::cout << YELLOW << "Triangle formé par les points : " << RESET << std::endl;
	std::cout << "- A(0, 0)" << std::endl;
	std::cout << "- B(10, 0)" << std::endl;
	std::cout << "- C(5, 10)" << std::endl << std::endl;

	// Tests
	test(a, b, c, Point(5, 5));      // Intérieur ✔️
	test(a, b, c, Point(5, 10));     // Sommet ❌
	test(a, b, c, Point(0, 0));      // Sommet ❌
	test(a, b, c, Point(5, 0));      // Bord ❌
	test(a, b, c, Point(10, 10));    // Extérieur ❌
	test(a, b, c, Point(4.9f, 4.9f));// Presque centre ✔️

	return 0;
}	