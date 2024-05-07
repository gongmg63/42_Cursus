#include "Harl.hpp"

int main(int ac, char *av[])
{
	Harl	harl;

	if (ac != 2)
	{
		std::cout << "Enter [ DEBUG ] [ INFO ] [ WARNING ] [ ERROR ] only" << std::endl;
		return (0);
	}
	harl.complain(std::string(av[1]));
	return (0);
}