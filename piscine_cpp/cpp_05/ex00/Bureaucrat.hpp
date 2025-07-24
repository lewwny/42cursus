/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:31:10 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/24 15:01:18 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
#include <iostream>
#include <string>
#include <exception>

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;
public:
	Bureaucrat( void );
	Bureaucrat(const std::string &name, int grade);
	Bureaucrat(const Bureaucrat &src);
	~Bureaucrat( void );

	Bureaucrat&			operator=(const Bureaucrat &src);
	const std::string&	getName( void ) const;
	int					getGrade( void ) const;
	void				incrementGrade( void );
	void				decrementGrade( void );

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
};

std::ostream& operator<<(std::ostream &out, const Bureaucrat& bureaucrat);

#endif