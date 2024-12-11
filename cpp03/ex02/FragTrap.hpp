#pragma once
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
public:
	FragTrap	();
	FragTrap	(const FragTrap& copy);
	FragTrap	(const std::string& name, unsigned int hp = 100, unsigned int ep = 100, unsigned int ad = 30);
	FragTrap&	operator=(const FragTrap& copy);
	~FragTrap	();
	void		attack(const std::string& target);
	void		highFivesGuys();
};