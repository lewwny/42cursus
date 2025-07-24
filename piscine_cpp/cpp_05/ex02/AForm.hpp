/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:08:51 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 18:33:28 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AForm_HPP
#define AForm_HPP
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
private:
	const std::string	_name;
	const int			_tosign;
	const int			_toexec;
	bool				_issigned;
public:
	AForm( void );
	AForm(const std::string &name, int tosign, int toexec);
	AForm(const AForm &src);
	virtual ~AForm( void );

	AForm&				operator=(const AForm &src);
	const std::string&	getName( void ) const;
	int			getToSign( void ) const;
	int			getToExec( void ) const;
	bool				getIsSigned( void ) const;

	class GradeToHighException : public std::exception {
		public: const char* what() const throw() {
			return "Grade is too high !";
		}
	};
	class GradeToLowException : public std::exception {
		public: const char* what() const throw() {
			return "Grade is too low !";
		}
	};
	
	class IsNotSigned : public std::exception {
		public: const char* what() const throw() {
			return "The form isn't signed";
		}
	};

	void			beSigned(const Bureaucrat& bureaucrat);
	virtual void	execute(const Bureaucrat& executor) const = 0;
	void			check_signed_toexec(const Bureaucrat& executor, int toexec) const;
};

std::ostream& operator<<(std::ostream &out, const AForm& AForm);

#endif