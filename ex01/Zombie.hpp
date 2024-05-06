#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__
#include <iostream>
#include <string>

class Zombie
{
private:
	std::string name;
public:
	void	set_name(std::string);
	void	announce(void) const;
};

Zombie*	zombieHorde(int N, std::string name);

#endif