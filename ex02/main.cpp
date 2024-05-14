#include "FragTrap.hpp"

int	main()
{
	FragTrap ft;
	FragTrap ft2("kong");

	ft.attack("kong");
	ft.set_name("min");
	ft.attack("kong");

	ft2.attack("min");
	ft2.highFivesGuys();
}