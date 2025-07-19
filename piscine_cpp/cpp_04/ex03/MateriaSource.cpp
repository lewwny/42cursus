/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:51:10 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:05:33 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; ++i)
		materias[i] = 0;
	// std::cout << "\033[32mMateriaSource default constructor called\033[0m" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	for (int i = 0; i < 4; ++i) {
		if (other.materias[i])
			materias[i] = other.materias[i]->clone();
		else
			materias[i] = 0;
	}
	// std::cout << "\033[32mMateriaSource copy constructor called\033[0m" << std::endl;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	if (this != &other) {
		for (int i = 0; i < 4; ++i) {
			delete materias[i];
			if (other.materias[i])
				materias[i] = other.materias[i]->clone();
			else
				materias[i] = 0;
		}
	}
	// std::cout << "\033[32mMateriaSource assignment operator called\033[0m" << std::endl;
	return *this;
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; ++i) {
		delete materias[i];
	}
	// std::cout << "\033[31mMateriaSource destructor called\033[0m" << std::endl;
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m) {
		std::cout << "\033[31mCannot learn null materia\033[0m" << std::endl;
		return;
	}
	for (int i = 0; i < 4; ++i) {
		if (!materias[i]) {
			materias[i] = m;
			// std::cout << "\033[32mLearned materia: " << m->getType() << "\033[0m" << std::endl;
			return;
		}
	}
	std::cout << "\033[31mMateriaSource is full, cannot learn more materias\033[0m" << std::endl;
}

AMateria* MateriaSource::createMateria(const std::string& type) {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] && materias[i]->getType() == type) {
			// std::cout << "\033[32mCreating materia of type: " << type << "\033[0m" << std::endl;
			return materias[i]->clone();
		}
	}
	std::cout << "\033[31mMateria of type " << type << " not found\033[0m" << std::endl;
	return 0;
}