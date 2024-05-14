#include "ClapTrap.hpp"

int	main()
{
	ClapTrap ct;
	ClapTrap ct2("kong");

	ct.attack("kong");
	ct.set_name("min");
	ct.attack("kong");
	ct.takeDamage(11);
	ct.takeDamage(10);

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
}