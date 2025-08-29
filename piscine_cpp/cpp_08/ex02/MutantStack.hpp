/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:43:52 by lengarci          #+#    #+#             */
/*   Updated: 2025/08/05 15:55:05 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>

template <typename T>
class MutantStack : public std::stack<T> {
public:
	typedef std::stack<T> stack;
	typedef typename stack::container_type container;
	typedef typename container::iterator iterator;
	MutantStack() : stack() {}
	MutantStack(const MutantStack& other) : stack(other) {}
	MutantStack& operator=(const MutantStack& other) {
		std::stack<T>::operator=(other);
		return *this;
	}
	~MutantStack() {}
	iterator begin() {
		return this->c.begin();
	}
	iterator end() {
		return this->c.end();
	}
};

#endif