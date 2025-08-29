/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:27:44 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/08/29 14:33:58 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No input provided." << std::endl;
		return 1;
	}

	PmergeMe sorter;

	try
	{
		sorter.sort(argv);
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}