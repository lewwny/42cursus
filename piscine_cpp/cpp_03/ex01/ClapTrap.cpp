/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:29:54 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/15 09:19:25 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	_name = "noname";
	_hitPoints = 10;
	_energyPoints = 10;
	_attackDamage = 0;
	std::cout << "ClapTrap default constructor called for " << _name << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
{
	_name = name;
	_hitPoints = 10;
	_energyPoints = 10;
	_attackDamage = 0;
	std::cout << "ClapTrap constructor called for " << _name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& src)
{
	_name = src._name;
	_hitPoints = src._hitPoints;
	_energyPoints = src._energyPoints;
	_attackDamage = src._attackDamage;
	std::cout << "ClapTrap copy constructor called for " << _name << std::endl;
}

ClapTrap	ClapTrap::operator=(const ClapTrap& src)
{
	_name = src._name;
	_hitPoints = src._hitPoints;
	_energyPoints = src._energyPoints;
	_attackDamage = src._attackDamage;
	std::cout << "ClapTrap assignment operator called for " << _name << std::endl;
	return *this;
}

ClapTrap::~ClapTrap() 
{
	std::cout << "ClapTrap destructor called for " << _name << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (!_energyPoints)
		std::cout << _name << " doesn't have energy points and can't attack" << std::endl;
	else
	{
		_energyPoints--;
		std::cout << "ClapTrap " << _name << " attacks " << target
		<< ", causing " << _attackDamage << " points of damage !" << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	_hitPoints -= amount;
	if (_hitPoints < 0)
		_hitPoints = 0;
	std::cout << "ClapTrap " << _name << " took damage and have "
	<< _hitPoints << " hitPoints..." << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (!_energyPoints)
		std::cout << _name << " can't be repaired beaucause it doesn't have energy points"
		<< std::endl;
	else
	{
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " be repaired and won " 
	<< amount << " hit points. Now it have " << _hitPoints << " hit points !"
	<< std::endl;
	}
}