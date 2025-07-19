/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:38:48 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/16 12:19:31 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

class Weapon 
{
private:
	std::string	_type;
public:
	Weapon(const std::string& type);
	~Weapon();
	void	setType(const std::string& type);
	const std::string&	gettype(void) const;
};

#endif