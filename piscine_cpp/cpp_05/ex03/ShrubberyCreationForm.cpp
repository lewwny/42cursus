/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:49:26 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 19:15:58 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyCreationForm", 145, 137),
												_target("defaultarget")
{}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target):
											AForm("ShrubberyCreationForm", 145, 137),
											_target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src):
											AForm(src), _target(src._target)
{}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& src)
{
	if (this != &src)
	{
		AForm::operator=(src);
		_target = src._target;
	}
	return *this;
}

const std::string&		ShrubberyCreationForm::getTarget( void ) const
{
	return _target;
}

void			ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
	check_signed_toexec(executor, getToExec());
	std::ofstream ofs((_target + "_shrubbery").c_str());
	if (!ofs)
		throw std::runtime_error("Cannot open file");
	ofs << "       /\\\n";
	ofs << "      /**\\\n";
	ofs << "     /****\\\n";
	ofs << "    /******\\\n";
	ofs << "   /********\\\n";
	ofs << "       ||\n";
	ofs << "       ||\n";

	ofs.close();
}