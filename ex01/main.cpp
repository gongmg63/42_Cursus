#include "Zombie.hpp"

// void	check(void)
// {
// 	system("leaks ex01");
// }

int main(void)
{
	Zombie	*zombie = zombieHorde(8, "foo");

	// atexit(check);
	for (int i = 0; i < 8; ++i)
	{
		std::cout << i << " ";
		zombie[i].announce();
	}
	delete []zombie;
	return (0);
}
