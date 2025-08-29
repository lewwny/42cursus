/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 15:37:23 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void Span::addNumber(int n) {
	if (_numbers.size() >= _max_size) {
		throw std::runtime_error("Cannot add more numbers, span is full");
	}
	_numbers.push_back(n);
}

int Span::shortestSpan()
{
	if (_numbers.size() < 2) {
		throw std::runtime_error("Not enough numbers to find a span");
	}
	std::vector<int> sorted_numbers = _numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());
	int shortest = std::numeric_limits<int>::max();
	for (size_t i = 1; i < sorted_numbers.size(); ++i) {
		int span = sorted_numbers[i] - sorted_numbers[i - 1];
		if (span < shortest) {
			shortest = span;
		}
	}
	return shortest;
}

int Span::longestSpan()
{
	if (_numbers.size() < 2) {
		throw std::runtime_error("Not enough numbers to find a span");
	}
	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());
	return max - min;
}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		_numbers = other._numbers;
		_max_size = other._max_size;
	}
	return *this;
}