/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:49:03 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 13:50:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>
#include <string>

template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T min(const T &a, const T &b) {
	if (a < b)
		return a;
	return b;
}

template <typename T>
T max(const T &a, const T &b) {
	if (a > b)
		return a;
	return b;
}

#endif