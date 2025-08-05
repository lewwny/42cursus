/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:03:08 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 14:22:05 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
	std::cout << "🔹 Test 1: Construction sans paramètre\n";
	Array<int> emptyArray;
	std::cout << "Size: " << emptyArray.size() << "\n\n";

	std::cout << "🔹 Test 2: Construction avec taille n\n";
	Array<int> intArray(5);
	std::cout << "Size: " << intArray.size() << "\n";
	for (unsigned int i = 0; i < intArray.size(); ++i)
		std::cout << "intArray[" << i << "] = " << intArray[i] << "\n";
	std::cout << "\n";

	std::cout << "🔹 Test 3: Affectation de valeurs dans l'array\n";
	for (unsigned int i = 0; i < intArray.size(); ++i)
		intArray[i] = i * 10;
	for (unsigned int i = 0; i < intArray.size(); ++i)
		std::cout << "intArray[" << i << "] = " << intArray[i] << "\n";
	std::cout << "\n";

	std::cout << "🔹 Test 4: Construction par copie\n";
	Array<int> copyArray(intArray);
	std::cout << "Modifying copyArray...\n";
	copyArray[0] = 999;
	std::cout << "copyArray[0] = " << copyArray[0] << "\n";
	std::cout << "intArray[0]  = " << intArray[0] << " (should not be affected)\n\n";

	std::cout << "🔹 Test 5: Opérateur d'affectation\n";
	Array<int> assignedArray;
	assignedArray = intArray;
	std::cout << "Modifying assignedArray...\n";
	assignedArray[1] = 888;
	std::cout << "assignedArray[1] = " << assignedArray[1] << "\n";
	std::cout << "intArray[1]      = " << intArray[1] << " (should not be affected)\n\n";

	std::cout << "🔹 Test 6: Accès hors limites (exception)\n";
	try {
		std::cout << "Accessing intArray[42]...\n";
		std::cout << intArray[42] << "\n"; // should throw
	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << "\n\n";
	}

	std::cout << "🔹 Test 7: Classe avec std::string\n";
	Array<std::string> strArray(2);
	strArray[0] = "Hello";
	strArray[1] = "World";
	for (unsigned int i = 0; i < strArray.size(); ++i)
		std::cout << "strArray[" << i << "] = " << strArray[i] << "\n";

	return 0;
}
