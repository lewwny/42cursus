/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:03:31 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/14 14:57:30 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "contact.hpp"

class Phonebook
{
private:
	Contact	_contacts[8];
	int	_index;
public:
	Phonebook();
	~Phonebook();
	void	addcontact();
	void	displaycontacts() const;
	void	displayonecontact(int index) const;
	int		getindex() const;
};

#endif