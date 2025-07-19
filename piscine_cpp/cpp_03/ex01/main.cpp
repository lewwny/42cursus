/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:29:26 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/14 21:12:00 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

#define RESET      "\033[0m"
#define GREEN      "\033[32m"
#define RED        "\033[31m"
#define BLUE       "\033[34m"
#define YELLOW     "\033[33m"
#define BOLD       "\033[1m"

int main() {
    std::cout << BOLD << YELLOW << "=== TESTS SCAVTRAP ===" << RESET << std::endl << std::endl;

    {
        std::cout << BOLD << GREEN << "[1] Construction d'un ScavTrap Serena" << RESET << std::endl;
        ScavTrap serena("Serena");

        std::cout << std::endl << BOLD << GREEN << "[2] Test de la méthode attack()" << RESET << std::endl;
        serena.attack("TargetBot");

        std::cout << std::endl << BOLD << GREEN << "[3] Test de guardGate()" << RESET << std::endl;
        serena.guardGate();

        std::cout << std::endl << BOLD << GREEN << "[4] Test du constructeur de copie" << RESET << std::endl;
        ScavTrap clone(serena);

        std::cout << std::endl << BOLD << GREEN << "[5] Test de l'opérateur d'affectation" << RESET << std::endl;
        ScavTrap another("Clone2");
        another = serena;

        std::cout << std::endl << BOLD << GREEN << "[6] Test d'une attaque multiple" << RESET << std::endl;
        for (int i = 0; i < 3; ++i)
            serena.attack("DummyBot");

        std::cout << std::endl << BOLD << GREEN << "[7] Fin du scope → Destructeurs" << RESET << std::endl;
    }

    std::cout << std::endl << BOLD << YELLOW << "=== FIN DES TESTS ===" << RESET << std::endl;
    return 0;
}