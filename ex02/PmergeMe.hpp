#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <exception>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <list>

class PmergeMe 
{
public:
	PmergeMe();
	PmergeMe(int ac, char* av[]);
	PmergeMe(const PmergeMe& copy);
	PmergeMe&	operator=(const PmergeMe& copy);
	~PmergeMe();

	void	sortVector();
	void	sortList();
private:
	std::vector<int>	_vec;
	std::list<int>		_list;

	void	inputValue(int ac, char* av[]);
	void	mergeInsertionVector(std::vector<int>& vec, std::vector<int>& sub_vec);
	void	mergeInsertionList(std::list<int> list);
};

template<typename T>
void	printArray(T container)
{
	for (std::size_t i = 0; i < container.size(); ++i)
		std::cout << container[i] << " ";
	std::cout << "\n";
}

template<typename T>
int	binarySearch(T container, int low, int high, int find)
{
	int mid;

	while (true)
	{
		mid = low + (high - low) / 2;
		if (high - low <= 1)
		{ 
			if (container[low] <= find)
				return find < container[high] ? high : high + 1;
			else
				return low;
		}
		if (find < container[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

#endif