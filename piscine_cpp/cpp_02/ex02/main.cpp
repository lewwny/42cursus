/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:24:22 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 15:04:55 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main( void )
{
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << a + b << std::endl;
	Fixed c;
	c = b - a;
	Fixed d(a);
	std::cout << "c : " << c << "et d : " << d << std::endl;
	std::cout << "le min entre c et d : " << Fixed::min(c, d) << std::endl;
	Fixed test;
	test = b / 0;
	std::cout << test << std::endl;
	return 0;
}