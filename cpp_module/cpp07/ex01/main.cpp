#include "iter.hpp"
#include <iostream>

template<typename T>
void	print(const T& a)
{
	std::cout << a << " ";
}

void	plusOne(int& num)
{
	++num;
}

int main()
{
	int arr1[] = {1, 2, 3, 4, 5};
	std::string arr2[] = {"a", "b", "c", "d", "e"};

	iter(arr1, 5, print<int>);
	std::cout << "\n";
	iter(arr2, 5, print<std::string>);
	std::cout << "\n";
	iter(arr1, 5, plusOne);
	iter(arr1, 5, print<int>);
	std::cout << "\n";
	
}