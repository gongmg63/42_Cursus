#pragma once
#include <iostream>

class ClapTrap
{
private:
	std::string		name;
	unsigned int	max_hit_point;
	unsigned int	hit_point;
	unsigned int	energy_point;
	unsigned int	attack_damage;
public:
	ClapTrap	();
	ClapTrap	(const ClapTrap& copy);
	ClapTrap	(const std::string& name, unsigned int hp = 10, unsigned int ep = 10, unsigned ad = 0);
	ClapTrap&	operator=(const ClapTrap& copy);
	~ClapTrap	();
	void		set_name(const std::string& name);
	void		attack(const std::string& target);
	void		takeDamage(unsigned int amount);
	void		beRepaired(unsigned int amount);
};