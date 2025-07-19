/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:34:57 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/14 18:54:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	std::cout << "\033[31mFirst test, randomChump :\033[0m" << std::endl;
	randomChump("CHUMP");
	std::cout << "\033[31mSecond test, newZombie :\033[0m" << std::endl;
	Zombie *z = newZombie("NEWZ");
	z->announce();
	delete z;
}