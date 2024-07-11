#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <exception>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <deque>
#include <ctime>

class PmergeMe 
{
public:
	PmergeMe();
	PmergeMe(int ac, char* av[]);
	PmergeMe(const PmergeMe& copy);
	PmergeMe&	operator=(const PmergeMe& copy);
	~PmergeMe();

	void	sortVector();
	void	sortDeque();
	void	printVectorDuration();
	void	printDequeDuration();
	void	inputValue(int ac, char* av[]);
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
	bool				_check_set;
	double				_vec_duration;
	double				_deq_duration;

	void	mergeInsertionVector(std::vector<int>& vec, std::vector<int>& sub_vec);
	void	mergeInsertionDeque(std::deque<int>& deque, std::deque<int>& sub_deque);
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