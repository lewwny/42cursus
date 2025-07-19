/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:20 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/14 19:16:50 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main(void)
{
	std::string brain = "HI THIS IS BRAIN";

	std::string* stringPTR = &brain;
	std::string& stringREF = brain;

	std::cout << "Memory address of brain     : " << &brain << std::endl;
	std::cout << "Memory address of stringPTR : " << stringPTR << std::endl;
	std::cout << "Memory address of stringREF : " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "Value of brain     :" << brain << std::endl;
	std::cout << "Value of stringPTR :" << *stringPTR << std::endl;
	std::cout << "Value of stringREF :" << stringREF << std::endl;
	return (0);
}