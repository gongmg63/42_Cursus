#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <exception>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cerrno>
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
		if (high - low < 3)
		{
			if (high - low == 2)
			{
				if (find >= container[mid] && find <= container[high])
					return high;
				if (find <= container[mid] && find >= container[low])
					return mid;
			}
			if (find >= container[high])
				return high + 1;
			if (find <= container[low])
				return low;
			return high;
		}
		if (find < container[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

template<typename T>
bool	checkSort(T container)
{
	for (std::size_t i = 0; i < container.size() - 1; ++i)
	{
		if (container[i] > container[i + 1])
		{
			std::cout << i << " " << i + 1 << "\n";
			return false;
		}
	}
	return true;
}

template<typename T>
void	indexingContainer(T sort_con, T& con, T& sub_con)
{
	T	check(con.size(), 0);

	for (std::size_t i = 0; i < sort_con.size(); ++i)
	{
		for (std::size_t j = 0; j < con.size(); ++j)
		{
			if (!check[j] && con[j] == sort_con[i] && i != j)
			{
				std::swap(con[i], con[j]);
				std::swap(sub_con[i], sub_con[j]);
				check[i] = 1;
			}
		}
	}
}

template<typename T>
T	mergeInsertion(T main_chain, T sub_chain)
{
	T	sort_con;

	sort_con.push_back(sub_chain[0]);
	sort_con.push_back(main_chain[0]);

	std::size_t	pre_jacob = 1;
	std::size_t	jacob = 1;
	int	tmp;
	while (jacob <= sub_chain.size())
	{
		tmp = jacob;
		jacob = jacob + 2 * pre_jacob;
		pre_jacob = tmp;
		for (std::size_t i = pre_jacob; i < (jacob > main_chain.size() ? main_chain.size() : jacob); ++i)
			sort_con.push_back(main_chain[i]);
		
		for (std::size_t i = (jacob > sub_chain.size() ? sub_chain.size() : jacob); i > pre_jacob; --i)
		{
			std::size_t	insert_idx = binarySearch(sort_con, 0, std::distance(sort_con.begin(), std::find(sort_con.rbegin(), sort_con.rend(), main_chain[i - 2]).base()) - 1, sub_chain[i - 1]);
			if (insert_idx == sort_con.size())
				sort_con.push_back(sub_chain[i - 1]);
			else
				sort_con.insert(sort_con.begin() + insert_idx, sub_chain[i - 1]);
			printArray(sort_con);
		}
	}
	return sort_con;
}

#endif