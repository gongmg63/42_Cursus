#pragma once
#include "ICharacter.hpp"
#include <iostream>

class Character : public ICharacter
{
private:
	std::string	name;
	AMateria*	m[4];
public:
	//OCCF
	Character 	();
	Character 	(const Character& copy);
	Character&	operator=(const Character& copy);
	~Character	();

	//constructor
	Character	(const std::string& name);

	//member function
	void	setName(const std::string& name);

	//override
	std::string const & getName() const;
	void				equip(AMateria* m);
	void				unequip(int idx);
	void				use(int idx, ICharacter& target);
};