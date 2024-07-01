#include "Array.hpp"

template<typename T>
Array<T>::Array()
	: _size(0), _array(NULL) {}

template<typename T>
Array<T>::Array(unsigned int n)
	: _size(n), _array(n > 0 ? new T[n] : NULL) 
{
	for (std::size_t i = 0; i < n; ++i)
		_array[i] = T();
}

template<typename T>
Array<T>::Array(const Array& copy)
	: _size(copy._size), _array(_size > 0 ? new T[_size] : NULL)
{
	std::memcpy(_array, copy._array, _size * sizeof(T));
}

template<typename T>
Array<T>::~Array()
{
	delete[] _array;
}

template<typename T>
Array<T>&	Array<T>::operator=(const Array<T>& copy)
{
	if (*this != copy)
	{
		delete *this;
		*this = Array(copy);
	}
	return *this;
}

template<typename T>
T&	Array<T>::operator[](std::size_t n)
{
	if (n >= _size)
		throw std::out_of_range("Index out of range");
	return _array[n];
}

template<typename T>
const T&	Array<T>::operator[](std::size_t n) const
{
	if (n >= _size)
		throw std::out_of_range("Index out of range");
	return _array[n];
}

template<typename T>
std::size_t	Array<T>::size() const
{
	return _size;
}