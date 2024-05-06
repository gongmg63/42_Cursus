#include "Weapon.hpp"

Weapon::Weapon(void)
{
	this->type = "No weapon";
}

Weapon::Weapon(std::string type)
{
	this->type = type;
}

std::string Weapon::getType(void) const
{
	return (this->type);
}

void	Weapon::setType(std::string type)
{
	this->type = type;
}