/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:49:26 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 19:33:50 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("RobotomyRequestForm", 145, 137),
												_target("defaultarget")
{}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target):
											AForm("RobotomyRequestForm", 145, 137),
											_target(target)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src):
											AForm(src), _target(src._target)
{}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& src)
{
	if (this != &src)
	{
		AForm::operator=(src);
		_target = src._target;
	}
	return *this;
}

const std::string&		RobotomyRequestForm::getTarget( void ) const
{
	return _target;
}

void			RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
	check_signed_toexec(executor, getToExec());
	std::cout << "* some drilling noises *" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << getTarget() << " has been robotized !" << std::endl;
	else
		std::cout << "The robotomy failed..." << std::endl;
}