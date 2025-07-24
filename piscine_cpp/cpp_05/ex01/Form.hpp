/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:08:51 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 18:33:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Form_HPP
#define Form_HPP
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	const int			_tosign;
	const int			_toexec;
	bool				_issigned;
public:
	Form( void );
	Form(const std::string &name, int tosign, int toexec);
	Form(const Form &src);
	~Form( void );

	Form&				operator=(const Form &src);
	const std::string&	getName( void ) const;
	int			getToSign( void ) const;
	int			getToExec( void ) const;
	bool				getIsSigned( void ) const;

	class GradeToHighException : public std::exception {
		public: const char* what() const throw() {
			return "Grade is to high !";
		}
	};
	class GradeToLowException : public std::exception {
		public: const char* what() const throw() {
			return "Grade is to low !";
		}
	};

	void	beSigned(const Bureaucrat& bureaucrat);
};

std::ostream& operator<<(std::ostream &out, const Form& Form);

#endif