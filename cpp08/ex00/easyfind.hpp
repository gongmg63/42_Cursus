#ifndef __EASYFIND_HPP__
#define __EASYFIND_HPP__

#include <iostream>
#include <iterator>
#include <algorithm>
#include <exception>

template<typename T>
typename T::iterator	easyfind(T& container, int find_num)
{
	typename T::iterator it = std::find(container.begin(), container.end(), find_num);
	if (it != container.end())
		return it;
	throw std::runtime_error("Can't find the num\n");
}

template<typename T>
typename T::const_iterator	easyfind(const T& container, int find_num)
{
	typename T::const_iterator it = std::find(container.begin(), container.end(), find_num);
	if (it != container.end())
		return it;
	throw std::runtime_error("Can't find the num\n");
}

#endif