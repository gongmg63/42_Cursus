#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() 
{
	for (int i = 0; i < 4; ++i)
		this->m[i] = NULL;
}

Character::Character(const Character& copy)
{
	*this = copy;
}

Character& Character::operator=(const Character& copy)
{
	this->name = copy.name;
	for (int i = 0; i < 4; ++i)
	{
		if (this->m[i] != NULL)
		{
			delete this->m[i];
			this->m[i] = NULL;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if (copy.m[i] != NULL)
			this->m[i] = copy.m[i]->clone();
	}
	return (*this);
}

Character::~Character() 
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->m[i] != NULL)
		{
			delete this->m[i];
		}
	}
}

Character::Character(const std::string& name)
{
	this->name = name;
	for (int i = 0; i < 4; ++i)
		this->m[i] = NULL;
}

void	Character::setName(const std::string& name)
{
	this->name = name;
}

std::string const &	Character::getName() const
{
	return (this->name);
}

void	Character::equip(AMateria* m)
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->m[i] == NULL)
		{
			this->m[i] = m;
			return ;
		}
	}
	std::cout << "Can't equip. Character Materias is full."  << std::endl;
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx > 3)
		return ;
	if (!this->m[idx])
		std::cout << "Can't unequip. No Materias in " << idx << std::endl;
	else
	{
		this->m[idx] = NULL;
	}
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3)
		return ;
	if (this->m[idx])
		this->m[idx]->use(target);
	else
		std::cout << "Can't use. No Materias in " << idx << std::endl;
}