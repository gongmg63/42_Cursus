#pragma once
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
public:
	ScavTrap	();
	ScavTrap	(const ScavTrap& copy);
	ScavTrap	(const std::string& name, unsigned int hp = 100, unsigned int ep = 50, unsigned int ad = 20);
	ScavTrap&	operator=(const ScavTrap& copy);
	~ScavTrap	();
	void		attack(const std::string& target);
	void		guardGate();
};