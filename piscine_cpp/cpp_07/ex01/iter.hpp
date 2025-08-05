/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:53:25 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 13:59:12 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>

template <typename T, typename F>
void	iter(T* array, size_t length, F func)
{
	for (size_t i = 0; i < length ; ++i)
		func(array[i]);
}

#endif