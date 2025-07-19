/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:36:44 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/24 12:00:07 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Please use, ./sed filename s1 s2 !" << std::endl;
		return (1);
	}
	Sed test(argv[1], argv[2], argv[3]);
	return (0);
}