/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:45:24 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 14:47:06 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main() {
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	try {
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found value: " << *it << std::endl;
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		std::vector<int>::iterator it = easyfind(vec, 6);
		std::cout << "Found value: " << *it << std::endl;
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	try {
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "Found value: " << *it << std::endl;
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::list<int>::iterator it = easyfind(lst, 40);
		std::cout << "Found value: " << *it << std::endl;
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}