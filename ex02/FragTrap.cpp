#include "FragTrap.hpp"

FragTrap::FragTrap ()
	:ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	this->hit_point = 100;
	this->energy_point = 100;
	this->attack_damage = 30;
}

FragTrap::FragTrap (const FragTrap& copy)
	:ClapTrap()
{
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = copy;
}

FragTrap::FragTrap(const std::string& name, unsigned int hp, unsigned int ep, unsigned int ad)
	:ClapTrap(name, hp, ep, ad)
{
	std::cout << "FragTrap constructor with attributes called " << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& copy)
{
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	this->name = copy.name;
	this->max_hit_point = copy.max_hit_point;
	this->hit_point = copy.hit_point;
	this->energy_point = copy.energy_point;
	this->attack_damage = copy.attack_damage;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called : " << this->name << std::endl;
}

void	FragTrap::attack(const std::string& target)
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
	std::cout << "FragTrap " << this->name << " attacks " << target << ", causing " \
				<< this->attack_damage << " points of damage!" << std::endl;
	this->energy_point--;
	std::cout << "Present hit points : " << this->hit_point << " energy points : " \
				<< this->energy_point << std::endl;
}

void	FragTrap::highFivesGuys()
{
	if (this->hit_point == 0 || this->energy_point == 0)
	{
		std::cout << "Not enough energy.." << std::endl;
		std::cout << "hit points : " << this->hit_point << " energy points : " \
					<< this->energy_point << std::endl;
		return ;
	}
	std::cout << "FragTrap HighFivesGuys." << std::endl;
}