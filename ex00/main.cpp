#include "ClapTrap.hpp"

int	main()
{
	ClapTrap ct;
	ClapTrap ct2("kong");
	ClapTrap ct3(ct2);

	std::cout << "------------------------------------------" << std::endl;
	ct.attack("min");
	ct = ct2;
	ct.attack("min");
	ct.takeDamage(11);
	ct.takeDamage(10);

	std::cout << "------------------------------------------" << std::endl;
	ct2.attack("min");
	ct2.attack("min");
	ct2.attack("min");
	ct2.attack("min");
	ct2.attack("min");
	ct2.beRepaired(5);
	ct2.beRepaired(5);
	ct2.beRepaired(5);
	ct2.beRepaired(5);
	ct2.beRepaired(5);
	ct2.attack("min");
	ct2.beRepaired(5);
	ct2.takeDamage(5);

	std::cout << "------------------------------------------" << std::endl;
	ct3.takeDamage(1000);
	std::cout << "------------------------------------------" << std::endl;
}