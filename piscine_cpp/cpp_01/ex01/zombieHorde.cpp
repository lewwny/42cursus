/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:57:32 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/15 15:35:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	if (N < 1)
		return NULL;
	Zombie* horde = NULL;
	try {
		horde = new Zombie[N];
		for (int i = 0; i < N; i++)
			horde[i].setname(name);
	} catch (std::bad_alloc) {
		std::cerr << "Allocation failed." << std::endl;
		return NULL;
	}
	return (horde);
}