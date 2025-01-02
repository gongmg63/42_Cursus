#include "BitcoinExchange.hpp"

int main(int ac, char* av[])
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open input file\n";
		return 1;
	}

	try
	{
		BitcoinExchange bitcoin;
		bitcoin.calculateExchange(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}