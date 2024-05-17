#include "ScavTrap.hpp"

int	main()
{
	ScavTrap st;
	ScavTrap st2("kong");
	ScavTrap st3(st2);

	std::cout << "------------------------------------------" << std::endl;
	st.attack("min");
	st = st2;
	st.attack("min");

	std::cout << "------------------------------------------" << std::endl;
	st2.attack("min");
	st2.guardGate();
	
	std::cout << "------------------------------------------" << std::endl;
	st3.takeDamage(1000);
	st3.takeDamage(1000);
	std::cout << "------------------------------------------" << std::endl;

	ClapTrap *cs = new ClapTrap("kong");
	ClapTrap *cs2 = new ScavTrap("kong");
	std::cout << "------------------------------------------" << std::endl;
	cs->attack("min");
	cs2->attack("min");
	std::cout << "------------------------------------------" << std::endl;
	delete cs;
	delete cs2;

	// for (int i = 0; i < 50; ++i)
	// 	st.beRepaired(10);
	// st.attack("min");
	// st.guardGate();
}