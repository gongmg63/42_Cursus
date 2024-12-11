#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__
#include <iostream>

class Zombie
{
private:
	std::string name;
public:
	Zombie	(void);
	Zombie	(std::string name);
	~Zombie	(void);
	void	set_name(std::string);
	void	announce(void) const;
};

Zombie*	zombieHorde(int N, std::string name);

#endif