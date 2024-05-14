#include "ScavTrap.hpp"

int	main()
{
	ScavTrap st;
	ScavTrap st2("kong");

	st.attack("kong");
	st.set_name("min");
	st.attack("kong");

	st2.attack("min");
	st2.guardGate();
}