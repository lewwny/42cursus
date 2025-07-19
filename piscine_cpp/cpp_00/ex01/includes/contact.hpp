/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/15 12:58:53 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <cstdlib>

class Contact {
public:
	Contact();
	~Contact();

	void	setfirstname(const std::string &firstname);
	void	setlastname(const std::string &lastname);
	void	setnickname(const std::string &nickname);
	void	setdarkestsecret(const std::string &darkestsecret);
	void	setphonenumber(const std::string &phonenumber);

	std::string	getfirstname() const;
	std::string	getlastname() const;
	std::string	getnickname() const;
	std::string	getdarkestsecret() const;
	std::string	getphonenumber() const ;
private:
	std::string	_firstname;
	std::string	_lastname;
	std::string	_nickname;
	std::string	_darkestsecret;
	std::string	_phonenumber;
};

#endif