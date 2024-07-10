#include "PmergeMe.hpp"

int main(int ac, char* av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: no input\n";
		return 1;
	}
	PmergeMe ford(ac, av);
	ford.sortVector();
}