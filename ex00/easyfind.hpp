#pragma once

#include <iostream>
#include <algorithm>
#include <exception>

class NotFoundException : public std::exception
{
public:
	const char*	what() const throw()
	{
		return "Can't find the num\n";
	}	
};

template<typename T>
int	easyfind(T& container, int find_num)
{
	typename T::iterator it = std::find(container.begin(), container.end(), find_num);
	if (it != container.end())
		return *it;
	throw NotFoundException();	
}