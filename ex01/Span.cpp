#include "Span.hpp"

Span::Span(unsigned int n)
	: _size(n) {}

Span::Span(const Span& copy)
	:  _vec(copy._vec), _size(copy._size) {}

Span& 	Span::operator=(const Span& copy)
{
	_size = copy._size;
	_vec = copy._vec;
	return *this;
}

Span::~Span() {}

void	Span::addNumber(int n)
{
	if (_vec.size() == _size)
		throw std::runtime_error("Can't add more value..");
	_vec.push_back(n);
	std::sort(_vec.begin(), _vec.end());
}

void	Span::addNumbers(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	_vec.insert(_vec.end(), first, last);
	if (_size < _vec.size())
		throw std::runtime_error("Can't add all value..");
}

int	Span::shortestSpan() const
{
	int	shortest_span = -1;

	if (_vec.size() < 2)
		throw std::runtime_error("Not enough elements..");
	for (unsigned int i = 0; i < _vec.size() - 1; ++i)
	{
		if (_vec[i + 1] - _vec[i] < shortest_span || shortest_span == -1)
			shortest_span = _vec[i + 1] - _vec[i];
	}
	return shortest_span;
}

int	Span::longestSpan() const
{
	if (_vec.size() < 2)
		throw std::runtime_error("Not enough elements..");
	return _vec[_vec.size() - 1] - _vec[0];
}

unsigned int	Span::size() const
{
	return _size;
}