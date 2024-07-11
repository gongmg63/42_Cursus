#include "PmergeMe.hpp"

int main(int ac, char* av[])
{
	try
	{
		if (ac < 2)
			throw std::runtime_error("Error: no input");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		PmergeMe ford(ac, av);
		ford.sortVector();
		ford.sortDeque();
		ford.printVectorDuration();
		ford.printDequeDuration();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}