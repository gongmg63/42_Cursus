#include "Zombie.hpp"

int	main(void)
{
	Zombie*	zombie = newZombie("foo");

	zombie->announce();
	randomChump("goo");
	delete zombie;
	return (0);
}
