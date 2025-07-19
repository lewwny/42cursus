/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:41:05 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 12:19:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string& type)
{
	_type = type;
}

Weapon::~Weapon()
{}

void	Weapon::setType(const std::string& type)
{
	_type = type;
}

const std::string&	Weapon::gettype(void) const
{
	return _type;
}