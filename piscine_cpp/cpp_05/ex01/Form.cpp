/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:09:14 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 18:33:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form( void ) :_name("defaultname"), _tosign(1), _toexec(1), _issigned(false) {}

Form::Form(const std::string &name, int tosign, int toexec): _name(name),
			_tosign(tosign), _toexec(toexec), _issigned(false)
{
	if (tosign < 1 || toexec < 1)
		throw GradeToHighException();
	else if (tosign > 150 || toexec > 150)
		throw GradeToLowException();
}

Form::Form(const Form &src): _name(src._name), _tosign(src._tosign), _toexec(src._toexec),
							_issigned(src._issigned)
{}

Form::~Form() {}

Form&	Form::operator=(const Form &src)
{
	if (this != &src)
	{
		_issigned = src._issigned;
	}
	return *this;
}

const std::string&	Form::getName( void ) const
{
	return _name;
}

int			Form::getToSign( void ) const
{
	return _tosign;
}

int			Form::getToExec( void ) const
{
	return _toexec;
}

bool				Form::getIsSigned( void ) const
{
	return _issigned;
}

void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _tosign)
		throw GradeToLowException();
	_issigned = true;
}

std::ostream& operator<<(std::ostream &out, const Form& f)
{
	out << f.getName()
	   << ", Form " << (f.getIsSigned() ? "signed" : "not signed")
	   << ", requires grade " << f.getToSign()
	   << " to sign and " << f.getToExec() << " to execute.";
	return out;
}