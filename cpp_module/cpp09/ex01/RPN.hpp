#ifndef __RPN_HPP__
#define __RPN_HPP__

#include <iostream>
#include <exception>
#include <cctype>
#include <stack>

class RPN
{
public:
	RPN();
	RPN(const RPN& copy);
	~RPN();
	RPN&	operator=(const RPN& copy);

	int	calculateRPN(const std::string& input);
private:
	std::stack<int>	_stack;
};

#endif