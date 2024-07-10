#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int ac, char* av[]) 
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
	_list = copy._list;
	return *this;
}

PmergeMe::~PmergeMe() {}

void	PmergeMe::sortVector()
{
	std::vector<int> sub_vec;
	std::cout << "Before : ";
	printArray(_vec);
	mergeInsertionVector(_vec, sub_vec);
	std::cout << "After : ";
	printArray(_vec);
}

void	PmergeMe::inputValue(int ac, char* av[])
{
	char*	end;
	long	num;

	for (int i = 1; i < ac; ++i)
	{
		errno = 0;
		num = std::strtol(av[i], &end, 10);
		if (*end || errno == ERANGE || num < 0 || num > 2147483647)
			throw std::runtime_error("Error: input error " + std::string(av[i]));
		_vec.push_back(num);
		_list.push_back(num);
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
			std::size_t	insert_idx = binarySearch(sort_vec, 0, sort_vec.size() - 1, sub_chain[i - 1]);
			if (insert_idx == sort_vec.size())
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
			if (!check[j])
			{
				if (vec[j] == sort_vec[i])
				{
					std::swap(vec[i], vec[j]);
					std::swap(sub_vec[i], sub_vec[j]);
					check[j] = true;
				}
			}
		}
	}
}

void	PmergeMe::mergeInsertionList(std::list<int> list)
{
	(void)list;
}