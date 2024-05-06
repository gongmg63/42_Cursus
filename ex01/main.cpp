#include "Zombie.hpp"

int main(void)
{
	Zombie	*zombie = zombieHorde(8, "foo");

	for (int i = 0; i < 8; ++i)
	{
		std::cout << i << " ";
		zombie[i].announce();
	}
	delete []zombie;
	return (0);
}
