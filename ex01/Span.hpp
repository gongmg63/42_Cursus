#pragma once

#include <iostream>
#include <exception>
#include <set>

class Span
{
public:
	Span(unsigned int n);
	Span(const Span& copy);
	Span&	operator=(const Span& copy);
	~Span();

	void	addNumber(int n);
	int		shortestSpan() const;
	int		longestSpan() const;

	class FullSpanException : public std::exception
	{
	public:
		const char*	what() const throw();
	};

	class NotEnoughElementException : public std::exception
	{
	public:
		const char* what() const throw();
	};
private:
	unsigned int	_size;
	unsigned int	_real_size;
	std::set<int>	_set;
};
