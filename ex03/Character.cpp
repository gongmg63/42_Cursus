#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() 
{
	for (int i = 0; i < 4; ++i)
		m[i] = NULL;
}

Character::Character(const Character& copy)
{
	*this = copy;
}

Character& Character::operator=(const Character& copy)
{
	this->name = copy.name;
	for (int i = 0; i < 4; ++i)
		this->m[i] = copy.m[i];
	return (*this);
}

Character::~Character() {}

Character::Character(const std::string& name)
{
	this->name = name;
	for (int i = 0; i < 4; ++i)
		m[i] = NULL;
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
	std::cout << "Try to equip " << m->getType() << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		if (this->m[i] == NULL)
		{
			this->m[i] = m;
			return ;
		}
	}
	std::cout << "Materias is full.." << std::endl;
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx > 3)
		return ;
	std::cout << "Unequip " << idx << " : " << this->m[idx]->getType() << std::endl;
	this->m[idx] = NULL;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3)
		return ;
	if (this->m[idx])
		this->m[idx]->use(target);
}