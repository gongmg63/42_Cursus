#include <iostream>
#include <string>

int	main(int ac, char *av[])
{
	std::string	str;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	for (int i = 1; i < ac; ++i)
	{
		str = av[i];
		for (int i = 0; i < (int)str.size(); ++i)
		{
			str[i] = std::toupper(str[i]);
		}
		std::cout << str; 
	}
	std::cout << std::endl;
}