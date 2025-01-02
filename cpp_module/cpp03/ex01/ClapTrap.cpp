#include "ClapTrap.hpp"

ClapTrap::ClapTrap ()
	:name(""), max_hit_point(10), hit_point(10), energy_point(10), attack_damage(0) 
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap (const std::string& name, unsigned int hp, unsigned int ep, unsigned ad)
	:name(name), max_hit_point(hp), hit_point(hp), energy_point(ep), attack_damage(ad) 
{
	std::cout << "ClapTrap constructor with attributes called" << std::endl;
}

ClapTrap::ClapTrap (const ClapTrap& copy)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& copy)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	this->name = copy.name;
	this->max_hit_point = copy.max_hit_point;
	this->hit_point = copy.hit_point;
	this->energy_point = copy.energy_point;
	this->attack_damage = copy.attack_damage;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called : " << this->name << std::endl;
}

void	ClapTrap::set_name(const std::string& name)
{
	if (!name.length())
	{
		std::cout << "Name can't be empty string." << std::endl;
		return ;
	}
	std::cout << "Set name function called" << std::endl;
	this->name = name;
}

void	ClapTrap::attack(const std::string& target)
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
	std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " \
				<< this->attack_damage << " points of damage!" << std::endl;
	this->energy_point--;
	std::cout << "Present hit points : " << this->hit_point << " energy points : " \
				<< this->energy_point << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (!this->name.length())
	{
		std::cout << "Set name first." << std::endl;
		return ;
	}
	if (this->hit_point == 0)
	{
		std::cout << this->name << " has no hit point.." << std::endl;
		std::cout << "hit points : " << this->hit_point << std::endl; 
		return ;
	}
	std::cout << "ClapTrap " << this->name << " take " << amount << " damage." << std::endl;
	if (this->hit_point < amount)
		this->hit_point = 0;
	else
		this->hit_point -= amount;
	std::cout << "Present hit points : " << this->hit_point << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (!this->name.length())
	{
		std::cout << "Set name first." << std::endl;
		return ;
	}
	if (this->hit_point <= 0 || this->energy_point <= 0)
	{
		std::cout << "Not enough energy.." << std::endl;
		std::cout << "hit points : " << this->hit_point << " energy points : " \
					<< this->energy_point << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << this->name << " is repaired " << amount << std::endl;
	if (this->hit_point + amount < this->hit_point || this->hit_point + amount > this->max_hit_point)
		this->hit_point = this->max_hit_point;
	else
		this->hit_point += amount;
	this->energy_point--;
	std::cout << "Present hit points : " << this->hit_point << " energy points : " \
				<< this->energy_point << std::endl;
}