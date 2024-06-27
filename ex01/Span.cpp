#include "Span.hpp"

Span::Span(unsigned int n)
	: _size(n), _real_size(0) {}

Span::Span(const Span& copy)
	: _size(copy._size), _real_size(copy._real_size)
{
	_set = copy._set;
}

Span& 	Span::operator=(const Span& copy)
{
	_size = copy._size;
	_real_size = copy._real_size;
	_set = copy._set;
	return *this;
}

Span::~Span() {}

void	Span::addNumber(int n)
{
	if (_real_size == _size)
		throw FullSpanException();
	++_real_size;
	_set.insert(n);
}

int	Span::shortestSpan() const
{
	int	shortest_span = -1;

	if (_real_size < 2)
		throw NotEnoughElementException();
	for (std::set<int>::iterator it = _set.begin(); it != --_set.end(); ++it)
	{
		std::set<int>::iterator next_it = it;
		++next_it;
		if (*next_it - *it < shortest_span || shortest_span == -1)
			shortest_span = *next_it - *it;
	}
	return shortest_span;
}

int	Span::longestSpan() const
{
	if (_real_size < 2)
		throw NotEnoughElementException();
	return *(--_set.end()) - *_set.begin();
}

const char*	Span::FullSpanException::what() const throw()
{
	return "Can't add more number..\n";
}

const char* Span::NotEnoughElementException::what() const throw()
{
	return "Not enough elements..\n";
}