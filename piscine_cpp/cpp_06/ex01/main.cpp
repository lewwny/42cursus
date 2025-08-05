/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:21:07 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/01 14:24:54 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main()
{
	Data data = {42, 3.14f, 2.718245, 'A'};
	
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized data: " << raw << std::endl;

	Data* deserializedData = Serializer::deserialize(raw);
	std::cout << "Deserialized data: "
			  << "i=" << deserializedData->i << ", "
			  << "f=" << deserializedData->f << ", "
			  << "d=" << deserializedData->d << ", "
			  << "c=" << deserializedData->c << std::endl;

	return 0;
}