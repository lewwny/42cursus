/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:17:51 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/08/01 10:28:34 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Use ./program <toconvert>" << std::endl;
		return 1;
	}
	std::string arg(argv[1]);
	ScalarConverter::convert(arg);
	return 0;
}