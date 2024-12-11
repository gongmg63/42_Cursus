#include "ScalarConverter.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Input : [char | int | float | double] \n";
		return (1);
	}
	ScalarConverter::convert(av[1]);
}