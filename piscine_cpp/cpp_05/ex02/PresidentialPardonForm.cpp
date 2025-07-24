/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:49:26 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 19:36:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): AForm("PresidentialPardonForm", 145, 137),
												_target("defaultarget")
{}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target):
											AForm("PresidentialPardonForm", 145, 137),
											_target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src):
											AForm(src), _target(src._target)
{}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& src)
{
	if (this != &src)
	{
		AForm::operator=(src);
		_target = src._target;
	}
	return *this;
}

const std::string&		PresidentialPardonForm::getTarget( void ) const
{
	return _target;
}

void			PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	check_signed_toexec(executor, getToExec());
	std::cout << getTarget() << " has been pardonned by Zaphod Beeblerox" << std::endl;
}