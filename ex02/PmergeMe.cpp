#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
	: _check_set(false), _vec_duration(-1), _deq_duration(-1)
{}

PmergeMe::PmergeMe(int ac, char* av[])
	: _check_set(true), _vec_duration(-1), _deq_duration(-1)
{
	inputValue(ac, av);
}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& copy)
{
	_vec = copy._vec;
	_deq = copy._deq;
	return *this;
}

PmergeMe::~PmergeMe() {}

void	PmergeMe::sortVector()
{
	if (!_check_set)
		throw std::runtime_error("Error: No data");
	std::vector<int>	sub_vec;
	std::clock_t		start;
	std::clock_t		end;
	
	std::cout << "Vector Before : ";
	printArray(_vec);
	start = clock();
	mergeInsertionVector(_vec, sub_vec);
	end = clock();
	std::cout << "Vector After  : ";
	printArray(_vec);
	_vec_duration = static_cast<double>(end - start) / 1000000;
}

void	PmergeMe::sortDeque()
{
	if (!_check_set)
		throw std::runtime_error("Error: No data");
	std::deque<int> sub_vec;
	std::clock_t		start;
	std::clock_t		end;

	std::cout << "Deque Before  : ";
	printArray(_deq);
	start = clock();
	mergeInsertionDeque(_deq, sub_vec);
	end = clock();
	std::cout << "Deque After   : ";
	printArray(_deq);
	_deq_duration = static_cast<double>(end - start) / 1000000;
}

void	PmergeMe::printVectorDuration()
{
	if (_vec_duration == -1)
		throw std::runtime_error("Error: Can't print vector duration. Sort first.");
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << _vec.size() << " elements with std::[vector] : " << _vec_duration << " us\n";
}

void	PmergeMe::printDequeDuration()
{
	if (_deq_duration == -1)
		throw std::runtime_error("Error: Can't print deque duration. Sort first.");
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::[deque] : " << _deq_duration << " us\n";
}

void	PmergeMe::inputValue(int ac, char* av[])
{
	char*	end;
	long	num;

	_check_set = true;
	for (int i = 1; i < ac; ++i)
	{
		errno = 0;
		num = std::strtol(av[i], &end, 10);
		if (*end || errno == ERANGE || num < 0 || num > 2147483647)
			throw std::runtime_error("Error: input error " + std::string(av[i]));
		_vec.push_back(num);
		_deq.push_back(num);
	}
}

void	PmergeMe::mergeInsertionVector(std::vector<int>& vec, std::vector<int>& sub_vec)
{
	std::vector<int>	main_chain;
	std::vector<int>	sub_chain;
	std::vector<int>	sort_vec;
	
	if (vec.size() < 2)
		return ;
	for (std::size_t i = 0; i < vec.size() / 2; ++i)
	{
		main_chain.push_back(std::max(vec[2 * i], vec[2 * i + 1]));
		sub_chain.push_back(std::min(vec[2 * i], vec[2 * i + 1]));
	}
	if (vec.size() % 2)
		sub_chain.push_back(vec[vec.size() - 1]);
	mergeInsertionVector(main_chain, sub_chain);
	sort_vec.push_back(sub_chain[0]);
	sort_vec.push_back(main_chain[0]);
	if (sub_vec.size() && vec[0] != sub_chain[0])
		std::swap(sub_vec[0], sub_vec[1]);
	std::size_t	pre_jacob = 1;
	std::size_t jacob = 1;
	while (jacob <= sub_chain.size())
	{
		int tmp = jacob;
		jacob = jacob + 2 * pre_jacob;
		pre_jacob = tmp;
		for (std::size_t i = pre_jacob; i < (jacob > main_chain.size() ? main_chain.size() : jacob); ++i)
			sort_vec.push_back(main_chain[i]);
		for (std::size_t i = (jacob > sub_chain.size() ? sub_chain.size() : jacob); i > pre_jacob; --i)
		{
			std::size_t	insert_idx = binarySearch(sort_vec, 0, sort_vec.size(), sub_chain[i - 1]);
			if (insert_idx == sort_vec.size() + 1)
				sort_vec.push_back(sub_chain[i - 1]);
			else
				sort_vec.insert(sort_vec.begin() + insert_idx, sub_chain[i - 1]);
		}
	}
	if (!sub_vec.size())
	{
		_vec = sort_vec;
		return ;
	}
	std::vector<bool>	check(vec.size(), false);
	for (std::size_t i = 0; i < sort_vec.size(); ++i)
	{
		for (std::size_t j = 0; j < vec.size(); ++j)
		{
			if (!check[j] && vec[j] == sort_vec[i] && i != j)
			{
				std::swap(vec[i], vec[j]);
				std::swap(sub_vec[i], sub_vec[j]);
				check[i] = true;
			}
		}
	}
}

void	PmergeMe::mergeInsertionDeque(std::deque<int>& deq, std::deque<int>& sub_deq)
{
	std::deque<int>	main_chain;
	std::deque<int>	sub_chain;
	std::deque<int>	sort_deque;
	
	if (deq.size() < 2)
		return ;
	for (std::size_t i = 0; i < deq.size() / 2; ++i)
	{
		main_chain.push_back(std::max(deq[2 * i], deq[2 * i + 1]));
		sub_chain.push_back(std::min(deq[2 * i], deq[2 * i + 1]));
	}
	if (deq.size() % 2)
		sub_chain.push_back(deq[deq.size() - 1]);
	mergeInsertionDeque(main_chain, sub_chain);
	sort_deque.push_back(sub_chain[0]);
	sort_deque.push_back(main_chain[0]);
	std::size_t	pre_jacob = 1;
	std::size_t jacob = 1;
	while (jacob <= sub_chain.size())
	{
		int tmp = jacob;
		jacob = jacob + 2 * pre_jacob;
		pre_jacob = tmp;
		for (std::size_t i = pre_jacob; i < (jacob > main_chain.size() ? main_chain.size() : jacob); ++i)
			sort_deque.push_back(main_chain[i]);
		for (std::size_t i = (jacob > sub_chain.size() ? sub_chain.size() : jacob); i > pre_jacob; --i)
		{
			std::size_t	insert_idx = binarySearch(sort_deque, 0, sort_deque.size() - 1, sub_chain[i - 1]);
			if (insert_idx == sort_deque.size())
				sort_deque.push_back(sub_chain[i - 1]);
			else
				sort_deque.insert(sort_deque.begin() + insert_idx, sub_chain[i - 1]);
		}
	}
	if (!sub_deq.size())
	{
		_deq = sort_deque;
		return ;
	}
	std::deque<bool>	check(deq.size(), false);
	for (std::size_t i = 0; i < sort_deque.size(); ++i)
	{
		for (std::size_t j = 0; j < deq.size(); ++j)
		{
			if (!check[j] && deq[j] == sort_deque[i] && i != j)
			{
				std::swap(deq[i], deq[j]);
				std::swap(sub_deq[i], sub_deq[j]);
				check[i] = true;
			}
		}
	}
}