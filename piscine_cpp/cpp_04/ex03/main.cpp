/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:29 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:07:29 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

//CHATGPT MAIN
#include <iostream>
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

void separator(const std::string& title) {
	std::cout << "\n=== " << title << " ===\n\n";
}

int main() {
	separator("Basic Materia Creation");

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	separator("Create Character and Equip");

	ICharacter* me = new Character("me");
	AMateria* tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);

	tmp = src->createMateria("cure");
	me->equip(tmp);

	separator("Use Materias");

	ICharacter* bob = new Character("bob");
	me->use(0, *bob); // ice
	me->use(1, *bob); // cure

	separator("Test Invalid Indices");

	me->use(-1, *bob);
	me->use(4, *bob);

	separator("Test Inventory Full");

	me->equip(src->createMateria("ice"));
	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("ice")); // 5e -> doit être ignorée

	separator("Use Full Inventory");

	for (int i = 0; i < 4; i++)
		me->use(i, *bob);

	separator("Unequip Tests");

	me->unequip(2); // enlever une materia
	me->use(2, *bob); // rien ne doit se passer

	separator("Deep Copy Test");

	Character* copy = new Character(*(Character*)me); // constructeur de copie
	std::cout << "Copy name: " << copy->getName() << std::endl;
	copy->use(0, *bob); // ice
	copy->use(1, *bob); // cure

	separator("Assignment Test");

	Character assign("someone else");
	assign = *(Character*)me;
	assign.use(0, *bob);
	assign.use(1, *bob);

	separator("Test Unknown Materia");

	AMateria* unknown = src->createMateria("fire");
	if (!unknown)
		std::cout << "Unknown materia creation returned nullptr as expected.\n";

	separator("Free memory");

	delete unknown;
	delete copy;
	delete bob;
	delete me;
	delete src;

	separator("END");
	return 0;
}


//SUBJECT MAIN
// int main()
// {
// 	IMateriaSource* src = new MateriaSource();
// 	src->learnMateria(new Ice());
// 	src->learnMateria(new Cure());
// 	ICharacter* me = new Character("me");
// 	AMateria* tmp;
// 	tmp = src->createMateria("ice");
// 	me->equip(tmp);
// 	tmp = src->createMateria("cure");
// 	me->equip(tmp);
// 	ICharacter* bob = new Character("bob");
// 	me->use(0, *bob);
// 	me->use(1, *bob);
// 	delete bob;
// 	delete me;
// 	delete src;
// 	return 0;
// }