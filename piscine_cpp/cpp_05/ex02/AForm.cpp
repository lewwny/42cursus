/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:09:14 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 18:33:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm( void ) :_name("defaultname"), _tosign(1), _toexec(1), _issigned(false) {}

AForm::AForm(const std::string &name, int tosign, int toexec): _name(name),
			_tosign(tosign), _toexec(toexec), _issigned(false)
{
	if (tosign < 1 || toexec < 1)
		throw GradeToHighException();
	else if (tosign > 150 || toexec > 150)
		throw GradeToLowException();
}

AForm::AForm(const AForm &src): _name(src._name), _tosign(src._tosign), _toexec(src._toexec),
							_issigned(src._issigned)
{}

AForm::~AForm() {}

AForm&	AForm::operator=(const AForm &src)
{
	if (this != &src)
	{
		_issigned = src._issigned;
	}
	return *this;
}

const std::string&	AForm::getName( void ) const
{
	return _name;
}

int			AForm::getToSign( void ) const
{
	return _tosign;
}

int			AForm::getToExec( void ) const
{
	return _toexec;
}

bool				AForm::getIsSigned( void ) const
{
	return _issigned;
}

void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _tosign)
		throw GradeToLowException();
	_issigned = true;
}

std::ostream& operator<<(std::ostream &out, const AForm& f)
{
	out << f.getName()
	   << ", AForm " << (f.getIsSigned() ? "signed" : "not signed")
	   << ", requires grade " << f.getToSign()
	   << " to sign and " << f.getToExec() << " to execute.";
	return out;
}

void	AForm::check_signed_toexec(const Bureaucrat& executor, int toexec) const
{
	if (!_issigned)
		throw IsNotSigned();
	else if (executor.getGrade() > toexec)
		throw GradeToLowException();
}