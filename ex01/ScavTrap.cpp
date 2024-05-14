#include "ScavTrap.hpp"

ScavTrap::ScavTrap ()
	:ClapTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->hit_point = 100;
	this->energy_point = 50;
	this->attack_damage = 20;
}

ScavTrap::ScavTrap (const ScavTrap& copy)
	:ClapTrap()
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = copy;
}

ScavTrap::ScavTrap(const std::string& name, unsigned int hp, unsigned int ep, unsigned int ad)
	:ClapTrap(name, hp, ep, ad)
{
	std::cout << "ScavTrap constructor with attributes called " << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& copy)
{
	std::cout << "ScavTrap copy assignment operator called" << std::endl;
	this->name = copy.name;
	this->max_hit_point = copy.max_hit_point;
	this->hit_point = copy.hit_point;
	this->energy_point = copy.energy_point;
	this->attack_damage = copy.attack_damage;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called : " << this->name << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (!this->name.length())
	{
		std::cout << "Set name first." << std::endl;
		return ;
	}
	if (this->hit_point == 0 || this->energy_point == 0)
	{
		std::cout << "Not enough energy.." << std::endl;
		std::cout << "hit points : " << this->hit_point << " energy points : " \
					<< this->energy_point << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << this->name << " attacks " << target << ", causing " \
				<< this->attack_damage << " points of damage!" << std::endl;
	this->energy_point--;
	std::cout << "Present hit points : " << this->hit_point << " energy points : " \
				<< this->energy_point << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap is now in Gate keeper mode." << std::endl;
}