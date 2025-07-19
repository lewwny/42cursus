/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:13:30 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 13:22:05 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB(const std::string& name)
	:_name(name),
	_arm(NULL)
{

}

HumanB::~HumanB()
{}

void HumanB::attack() const
{
	if (_arm)
		std::cout << _name << " attacks with their " << (*_arm).gettype() << std::endl;
	else
		std::cout << _name << " can't attack. He doesn't have weapon." << std::endl;
}

void	HumanB::setWeapon(Weapon& arm)
{
	_arm = &arm;
}