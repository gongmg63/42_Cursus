#ifndef __SPAN_HPP__
#define __SPAN_HPP__

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <cmath>

class Span
{
public:
	Span(unsigned int n);
	Span(const Span& copy);
	Span&	operator=(const Span& copy);
	~Span();

	void	addNumber(int n);
	void	addNumbers(std::vector<int>::iterator first, std::vector<int>::iterator last);
	int		shortestSpan() const;
	int		longestSpan() const;

	unsigned int	size() const;
private:
	std::vector<int>	_vec;
	unsigned int		_size;
};

#endif