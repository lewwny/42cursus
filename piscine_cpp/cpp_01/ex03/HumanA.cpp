/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:54:10 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 12:22:30 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(const std::string& name, Weapon& arm)
	: _name(name),
	_arm(arm)
{}

HumanA::~HumanA()
{}

void HumanA::attack() const
{
	std::cout << _name << " attacks with their " << _arm.gettype() << std::endl;
}