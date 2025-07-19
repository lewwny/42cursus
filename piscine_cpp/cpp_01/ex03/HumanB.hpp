/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:12:37 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 13:18:25 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class	HumanB
{
private:
	std::string	_name;
	Weapon*	_arm;
public:
	HumanB(const std::string& name);
	~HumanB();

	void	attack() const;
	void	setWeapon(Weapon& arm);
};

#endif