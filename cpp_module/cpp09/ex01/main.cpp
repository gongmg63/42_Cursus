#include "RPN.hpp"

int main(int ac, char* av[])
{
	if (ac != 2)
	{
		std::cerr << "Error: input only one expression\n";
		return 1;
	}
	try
	{
		RPN rpn;
		int ret = rpn.calculateRPN(av[1]);
		std::cout << ret << "\n";
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}