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
	void	announce(void) const;
	~Zombie	(void);
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif