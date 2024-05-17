#pragma once
#include <iostream>

class ClapTrap
{
protected:
	std::string		name;
	unsigned int	max_hit_point;
	unsigned int	hit_point;
	unsigned int	energy_point;
	unsigned int	attack_damage;
public:
	//Constructor
	ClapTrap	();
	ClapTrap	(const ClapTrap& copy);
	ClapTrap	(const std::string& name, unsigned int hp = 10, unsigned int ep = 10, unsigned ad = 0);
	
	//Operator overload
	ClapTrap&	operator=(const ClapTrap& copy);
	
	//Destructor
	virtual ~ClapTrap	();

	//member function
	void			set_name(const std::string& name);
	virtual void	attack(const std::string& target);
	void			takeDamage(unsigned int amount);
	void			beRepaired(unsigned int amount);
};