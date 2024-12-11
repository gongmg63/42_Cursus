#include "PmergeMe.hpp"

int main(int ac, char* av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: no input\n";
		return 1;
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