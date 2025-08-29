/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:29:51 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/08/29 14:33:31 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

struct IdxCmpVec {
	const std::vector<int>* ref;
	IdxCmpVec(const std::vector<int>* r) : ref(r) {}
	bool operator()(std::size_t a, std::size_t b) const { return (*ref)[a] < (*ref)[b]; }
};

struct IdxCmpDeq {
	const std::deque<int>* ref;
	IdxCmpDeq(const std::deque<int>* r) : ref(r) {}
	bool operator()(std::size_t a, std::size_t b) const { return (*ref)[a] < (*ref)[b]; }
};

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::fillVectors(char **av)
{
	for (int i = 1; av[i]; i++)
	{
		std::istringstream iss(av[i]);
		int num;
		if (!(iss >> num) || num < 0 || !iss.eof())
			throw std::invalid_argument("Error: Invalid input. Only positive integers are allowed.");
		_vec.push_back(num);
	}
}

void PmergeMe::fillDeques(char **av)
{
	for (int i = 1; av[i]; i++)
	{
		std::istringstream iss(av[i]);
		int num;
		if (!(iss >> num) || num < 0 || !iss.eof())
			throw std::invalid_argument("Error: Invalid input. Only positive integers are allowed.");
		_deq.push_back(num);
	}
}

void PmergeMe::printContainers() const
{
	std::cout << "Vector: ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		std::cout << _vec[i];
		if (i < _vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "Deque: ";
	for (size_t i = 0; i < _deq.size(); i++)
	{
		std::cout << _deq[i];
		if (i < _deq.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

static void buildJacobsthalOrder(size_t n, std::vector<size_t> &order)
{
	order.clear();
	if (n == 0)
		return;
	std::vector<size_t> jacobsthal;
	size_t j0 = 0, j1 = 1;
	if (1<=n)
		jacobsthal.push_back(1);
	while (1)
	{
		size_t jn = j1 + 2 * j0;
		if (jn > n)
			break;
		jacobsthal.push_back(jn);
		j0 = j1;
		j1 = jn;
	}
	size_t prev = 0;
	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		size_t j = jacobsthal[i];
		for (size_t k = j - 1; k >= prev && k < n; k--)
			order.push_back(k);
		prev = j;
	}
	if (prev < n)
	{
		for (size_t k = n - 1; k >= prev; k--)
			order.push_back(k);
	}
}

static void buildJacobsthalOrder(size_t n, std::deque<size_t> &order)
{
	order.clear();
	if (n == 0)
		return;
	std::deque<size_t> jacobsthal;
	size_t j0 = 0, j1 = 1;
	if (1<=n)
		jacobsthal.push_back(1);
	while (1)
	{
		size_t jn = j1 + 2 * j0;
		if (jn > n)
			break;
		jacobsthal.push_back(jn);
		j0 = j1;
		j1 = jn;
	}
	size_t prev = 0;
	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		size_t j = jacobsthal[i];
		for (size_t k = j - 1; k >= prev && k < n; k--)
			order.push_back(k);
		prev = j;
	}
	if (prev < n)
	{
		for (size_t k = n - 1; k >= prev; k--)
			order.push_back(k);
	}
}

void PmergeMe::mergeInsertSortVector()
{
	if (_vec.size() <= 1)
		return;
	std::vector<int> big, small;
	bool stragg = false;
	for (size_t i = 0; i < _vec.size(); i += 2)
	{
		if (i + 1 < _vec.size())
		{
			if (_vec[i] > _vec[i + 1])
			{
				big.push_back(_vec[i]);
				small.push_back(_vec[i + 1]);
			}
			else
			{
				big.push_back(_vec[i + 1]);
				small.push_back(_vec[i]);
			}
		}
		else
		{
			small.push_back(_vec[i]);
			stragg = true;
		}
	}
	int straggler = -1;
	if (stragg)
	{
		straggler = small.back();
		small.pop_back();
	}
	std::vector<std::size_t> indices(big.size());
	for (std::size_t i = 0; i < big.size(); i++)
		indices[i] = i;
	std::sort(indices.begin(), indices.end(), IdxCmpVec(&big));
	std::vector<int> mainChain; mainChain.reserve(big.size());
	std::vector<int> pend; pend.reserve(small.size());
	for (size_t t = 0; t < indices.size(); t++)
	{
		size_t k = indices[t];
		mainChain.push_back(big[k]);
		pend.push_back(small[k]);
	}
	if (!pend.empty())
	{
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[0]);
		mainChain.insert(it, pend[0]);
	}
	std::vector<size_t> order;
	buildJacobsthalOrder(pend.size(), order);
	for (size_t i = 1; i < order.size(); i++)
	{
		size_t idx = order[i];
		int val = pend[idx];
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), val);
		mainChain.insert(it, val);
	}
	if (stragg)
	{
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}
	_vec = mainChain;
}

void PmergeMe::mergeInsertSortDeque()
{
	if (_deq.size() <= 1)
		return;
	std::deque<int> big, small;
	bool stragg = false;
	for (size_t i = 0; i < _deq.size(); i += 2)
	{
		if (i + 1 < _deq.size())
		{
			if (_deq[i] > _deq[i + 1])
			{
				big.push_back(_deq[i]);
				small.push_back(_deq[i + 1]);
			}
			else
			{
				big.push_back(_deq[i + 1]);
				small.push_back(_deq[i]);
			}
		}
		else
		{
			small.push_back(_deq[i]);
			stragg = true;
		}
	}
	int straggler = -1;
	if (stragg)
	{
		straggler = small.back();
		small.pop_back();
	}
	std::deque<std::size_t> indices(big.size());
	for (std::size_t i = 0; i < big.size(); i++)
		indices[i] = i;
	std::sort(indices.begin(), indices.end(), IdxCmpDeq(&big));
	std::deque<int> mainChain;
	std::deque<int> pend;
	for (size_t t = 0; t < indices.size(); t++)
	{
		size_t k = indices[t];
		mainChain.push_back(big[k]);
		pend.push_back(small[k]);
	}
	if (!pend.empty())
	{
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[0]);
		mainChain.insert(it, pend[0]);
	}
	std::deque<size_t> order;
	buildJacobsthalOrder(pend.size(), order);
	for (size_t i = 1; i < order.size(); i++)
	{
		size_t idx = order[i];
		int val = pend[idx];
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), val);
		mainChain.insert(it, val);
	}
	if (stragg)
	{
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}
	_deq = mainChain;
}

static long getTimeMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void PmergeMe::sort(char **argv)
{
	long start = getTimeMicroseconds();
	fillVectors(argv);
	std::vector<int> original = _vec;
	mergeInsertSortVector();
	long end = getTimeMicroseconds();
	long durationVec = end - start;
	start = getTimeMicroseconds();
	fillDeques(argv);
	mergeInsertSortDeque();
	end = getTimeMicroseconds();
	long durationDeq = end - start;
	std::cout << "Before: ";
	for (size_t i = 0; i < original.size(); i++)
	{
		std::cout << original[i];
		if (i < original.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		std::cout << _vec[i];
		if (i < _vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << durationVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : " << durationDeq << " us" << std::endl;
}