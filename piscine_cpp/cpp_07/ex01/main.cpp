/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:55:41 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 13:57:58 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp" // inclusion du fichier avec iter

// === Fonctions de test ===

// Affiche un élément (lecture seule)
template <typename T>
void printElement(const T& elem) {
	std::cout << elem << " ";
}

// Multiplie un entier par 2 (modification)
void doubleValue(int& x) {
	x *= 2;
}

// Ajoute un "!" à une string
void appendExclamation(std::string& s) {
	s += "!";
}

// Affiche une string en majuscules (lecture seule)
void printUpper(const std::string& s) {
	for (size_t i = 0; i < s.size(); ++i)
		std::cout << (char)std::toupper(s[i]);
	std::cout << " ";
}

int main() {
	// --- Tableaux de test ---

	int intArray[] = {1, 2, 3, 4, 5};
	size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << "Original int array: ";
	iter(intArray, intLen, printElement<int>);
	std::cout << "\n";

	iter(intArray, intLen, doubleValue);

	std::cout << "Doubled int array: ";
	iter(intArray, intLen, printElement<int>);
	std::cout << "\n\n";

	double doubleArray[] = {1.1, 2.2, 3.3};
	size_t doubleLen = sizeof(doubleArray) / sizeof(doubleArray[0]);

	std::cout << "Double array: ";
	iter(doubleArray, doubleLen, printElement<double>);
	std::cout << "\n\n";

	std::string strArray[] = {"hello", "world", "template"};
	size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << "Original string array: ";
	iter(strArray, strLen, printElement<std::string>);
	std::cout << "\n";

	iter(strArray, strLen, appendExclamation);

	std::cout << "Modified string array: ";
	iter(strArray, strLen, printElement<std::string>);
	std::cout << "\n";

	std::cout << "Uppercase print: ";
	iter(strArray, strLen, printUpper);
	std::cout << "\n";

	return 0;
}
