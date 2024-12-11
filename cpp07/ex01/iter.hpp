#pragma once

#include <cstdlib>

template<typename T1, typename T2>
void	iter(T1* array, std::size_t size, T2 f)
{
	for (std::size_t i = 0; i < size; ++i)
		f(array[i]);
}