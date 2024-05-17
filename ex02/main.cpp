#include "FragTrap.hpp"

int	main()
{
	FragTrap ft;
	FragTrap ft2("kong");
	FragTrap ft3(ft2);

	std::cout << "------------------------------------------" << std::endl;
	ft.attack("min");
	ft = ft2;
	ft.attack("min");

	std::cout << "------------------------------------------" << std::endl;
	ft2.attack("min");
	ft2.highFivesGuys();
	
	std::cout << "------------------------------------------" << std::endl;
	ft3.takeDamage(1000);
	ft3.takeDamage(1000);
	std::cout << "------------------------------------------" << std::endl;

	ClapTrap *cs = new ClapTrap("kong");
	ClapTrap *cs2 = new FragTrap("kong");
	std::cout << "------------------------------------------" << std::endl;
	cs->attack("min");
	cs2->attack("min");
	std::cout << "------------------------------------------" << std::endl;
	delete cs;
	delete cs2;

	// for (int i = 0; i < 100; ++i)
	// 	ft.beRepaired(10);
	// ft.attack("min");
	// ft.highFivesGuys();
}