/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:03:36 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 10:59:10 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phonebook.hpp"

static std::string	troncstr(const std::string &str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

Phonebook::Phonebook() 
{
	_index = 0;
}

Phonebook::~Phonebook() {}

void	Phonebook::displaycontacts() const
{
	if (!_index)
	{
		std::cout << "\033[31mPlease add a contact before trying to display the contacts.\033[0m" << std::endl;
		return ;
	}
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "|    Index|First name| Last name| Nickname|" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		if (i >= _index)
			break;
		std::cout << "|" << std::setw(10) << std::right << i + 1
				  << "|" << std::setw(10) << std::right << troncstr(_contacts[i].getfirstname())
				  << "|" << std::setw(10) << std::right << troncstr(_contacts[i].getlastname())
				  << "|" << std::setw(10) << std::right << troncstr(_contacts[i].getnickname()) << "|" << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
	}
}

void	Phonebook::addcontact()
{
	std::string	input;
	Contact new_contact;
	
	while (1)
	{
		std::cout << "Enter First name" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setfirstname(input);
		if (!input.empty() && input != "")
			break;
	}
	
	while (1)
	{
		std::cout << "Enter Last name" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setlastname(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "Enter Nickname" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setnickname(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "Enter Phone Number" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setphonenumber(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "Enter Darkest secret" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setdarkestsecret(input);
		if (!input.empty() && input != "")
			break;
	}
	_contacts[_index % 8] = new_contact;
	_index++;
}

void	Phonebook::displayonecontact(int index) const
{
	std::cout << "First name : \033[32m" << _contacts[index - 1].getfirstname() << "\033[0m" << std::endl;
	std::cout << "Last name : \033[32m" << _contacts[index - 1].getlastname() << "\033[0m" << std::endl;
	std::cout << "Nickname : \033[32m" << _contacts[index - 1].getnickname() << "\033[0m" << std::endl;
	std::cout << "Phone Number : \033[32m" << _contacts[index - 1].getphonenumber() << "\033[0m" << std::endl;
	std::cout << "Darkest secret \033[32m: " << _contacts[index - 1].getdarkestsecret() << "\033[0m" << std::endl;
}

int	Phonebook::getindex() const
{
	return (_index);
}