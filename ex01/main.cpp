#include "ScavTrap.hpp"

int	main()
{
	ScavTrap st;
	ScavTrap st2("kong");
	ScavTrap st3(st2);

	std::cout << "------------------------------------------" << std::endl;
	st.attack("kong");
	st = st2;
	st.attack("kong");

	std::cout << "------------------------------------------" << std::endl;
	st2.attack("min");
	st2.guardGate();
	
	std::cout << "------------------------------------------" << std::endl;
	st3.takeDamage(1000);
	std::cout << "------------------------------------------" << std::endl;
}