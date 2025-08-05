/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:03:11 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 14:24:38 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= this->size())
		throw std::out_of_range("Array index out of bounds");
	return this->_array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= this->size())
		throw std::out_of_range("Array index out of bounds");
	return this->_array[index];
}