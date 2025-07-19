/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:29:31 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/17 17:12:35 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() : _name("Default"), _idx(0) {
	for (int i = 0; i < 4; ++i)
		_inventory[i] = 0;
}

Character::Character(std::string name) : _name(name), _idx(0) {
	for (int i = 0; i < 4; ++i)
		_inventory[i] = 0;
}

Character::Character(const Character& other) : _name(other._name), _idx(other._idx) {
	for (int i = 0; i < 4; ++i) {
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = 0;
	}
}

Character::~Character() {
	for (int i = 0; i < 4; ++i) {
		delete _inventory[i];
	}
	// std::cout << "\033[31mCharacter destructor called for: " << _name << "\033[0m" << std::endl;
}

Character& Character::operator=(const Character& other) {
	if (this != &other) {
		_name = other._name;
		_idx = other._idx;
		for (int i = 0; i < 4; ++i) {
			delete _inventory[i];
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = 0;
		}
	}
	return *this;
}

const std::string& Character::getName() const {
	return _name;
}

void Character::equip(AMateria* m) {
	if (!m) {
		std::cout << "\033[33mCannot equip a null AMateria\033[0m" << std::endl;
		return;
	}
	if (_idx >= 4) {
		std::cout << "\033[33mInventory full, cannot equip " << m->getType() << ". Deleting it.\033[0m" << std::endl;
		delete m;
		return;
	}
	_inventory[_idx++] = m;
	std::cout << "\033[32mEquipped " << m->getType() << " to " << _name << " at slot " << (_idx-1) << "\033[0m" << std::endl;
}

void Character::unequip(int idx) {
	if (idx >= 0 && idx < 4 && _inventory[idx]) {
		std::cout << "\033[33mUnequipped " << _inventory[idx]->getType() << " from " << _name << "\033[0m" << std::endl;
		delete _inventory[idx];
		_inventory[idx] = 0;
	} else {
		std::cout << "\033[33mInvalid index or no AMateria to unequip\033[0m" << std::endl;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (idx >= 0 && idx < 4 && _inventory[idx]) {
		// std::cout << "\033[34m" << _name << " uses " << _inventory[idx]->getType() << " on " << target.getName() << "\033[0m" << std::endl;
		// _inventory[idx]->use(target);
		_inventory[idx]->use(target);
	} else {
		std::cout << "\033[33mInvalid index or no AMateria to use\033[0m" << std::endl;
	}
}