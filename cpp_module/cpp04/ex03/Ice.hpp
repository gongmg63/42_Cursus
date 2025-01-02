#pragma once
#include "AMateria.hpp"
#include "Character.hpp"

class Ice : public AMateria
{
public:
	//OCCF
	Ice	();
	Ice	(const Ice& copy);
	Ice&	operator=(const Ice& copy);
	~Ice	();

	//override
	AMateria*	clone() const;
	void		use(ICharacter& target);
};
