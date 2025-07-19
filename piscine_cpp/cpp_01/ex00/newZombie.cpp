/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:39:36 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/14 18:51:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
	Zombie *z = nullptr;
	try {
		z = new Zombie(name);
	} catch (std::bad_alloc) {
		std::cerr << "Allocation failed." << std::endl;
		return nullptr;
	}
	return (z);
}