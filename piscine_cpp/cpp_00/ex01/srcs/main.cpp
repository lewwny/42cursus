/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:23:35 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/14 14:45:26 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/contact.hpp"
#include "../includes/phonebook.hpp"

static void	search_func(Phonebook phonebook)
{
	std::string	input;
	int	number;
	phonebook.displaycontacts();
	if (!phonebook.getindex())
		return;
	while (1)
	{
		std::cout << "Enter the index of the contact thah you want to display : ";
		if (!std::getline(std::cin, input))
		{		
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		std::istringstream iss(input);
		if (iss >> number && iss.eof())
		{
			if (number > phonebook.getindex() || number < 1)
			{
				std::cout << "\033[31mPlease enter a correct index.\033[0m" << std::endl;
				continue ;
			}
			phonebook.displayonecontact(number);
			break;
		}
	}
	
}

int	main(void)
{
	Phonebook	phonebook;
	std::string	input;
	while (1)
	{
		std::cout << "Enter your command [ADD, SEARCH, EXIT]" << std::endl;
		std::cout << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			return (0);
		}
		else if (input == "EXIT")
			break ;
		else if (input == "ADD")
			phonebook.addcontact();
		else if (input == "SEARCH")
			search_func(phonebook);
	}
	std::cout << "\033[34mThank's for stopping by ! Good bye !\033[0m" << std::endl;
	return (0);
}