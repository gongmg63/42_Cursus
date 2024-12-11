#pragma once

#include <cstdlib>
#include <exception>

template<typename T>
class Array
{
public:
	Array	();
	Array	(unsigned int n);
	Array	(const Array& copy);
	~Array	();

	Array&		operator=(const Array& copy);
	T&			operator[](std::size_t n);
	const T&	operator[](std::size_t n) const;

	std::size_t	size() const;
private:
	std::size_t	_size;
	T*			_array;
};

#include "Array.tpp"
