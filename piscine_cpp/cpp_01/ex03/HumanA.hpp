/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:47:37 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 13:15:46 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class	HumanA
{
private:
	std::string	_name;
	Weapon&	_arm;
public:
	HumanA(const std::string& name, Weapon& arm);
	~HumanA();

	void	attack() const;
};

#endif