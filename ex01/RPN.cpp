#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& copy)
	: _stack(copy._stack) {}

RPN::~RPN() {}

RPN&	RPN::operator=(const RPN& copy)
{
	_stack = copy._stack;
	return *this;
}

int	RPN::calculateRPN(const std::string& input)
{
	int	lnum;
	int	rnum;

	for (std::size_t i = 0; i < input.size(); ++i)
	{
		if (input[i] == ' ')
			continue ;
		if (std::isdigit(input[i]))
		{
			_stack.push(input[i] - '0');
			continue ;
		}
		if (input[i] != '-' && input[i] != '+' && input[i] != '*' && input[i] != '/')
			throw std::runtime_error("Error: invalid input");
		if (_stack.size() < 2)
			throw std::runtime_error("Error: insufficient digit");
		rnum = _stack.top();
		_stack.pop();
		lnum = _stack.top();
		_stack.pop();
		if (input[i] == '+')
			_stack.push(lnum + rnum);
		else if (input[i] == '-')
			_stack.push(lnum - rnum);
		else if (input[i] == '*')
			_stack.push(lnum * rnum);
		else if (input[i] == '/')
		{
			if (rnum == 0)
				throw std::runtime_error("Error: couldn't divide by 0");
			_stack.push(lnum / rnum);
		}
	}
	if (_stack.size() == 0)
		throw std::runtime_error("Error: input nothing");
	if (_stack.size() != 1)
		throw std::runtime_error("Error: insufficient operator");
	lnum = _stack.top();
	_stack.pop();
	return lnum;
}