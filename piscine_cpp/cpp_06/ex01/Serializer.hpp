/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:18:57 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/01 14:24:25 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
#include <iostream>
#include <string>
#include <stdint.h>

struct Data
{
	int		i;
	float	f;
	double	d;
	char	c;
};

class Serializer
{
private:
	Serializer();
public:
	static uintptr_t	serialize(Data* ptr) {
		return reinterpret_cast<uintptr_t>(ptr);
	}
	static Data*		deserialize(uintptr_t raw) {
		return reinterpret_cast<Data*>(raw);
	}
};

#endif