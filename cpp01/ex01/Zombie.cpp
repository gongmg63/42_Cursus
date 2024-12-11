#include "Zombie.hpp"

Zombie::Zombie(void) {}

Zombie::Zombie(std::string name)
{
	this->name = name;
}

void	Zombie::announce(void) const
{
	std::cout << this->name << ": " << "BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::set_name(std::string name)
{
	this->name = name;
}

Zombie::~Zombie(void)
{
	std::cout << this->name << " is destroyed" << std::endl;
}