#pragma once
#include "AMateria.hpp"
#include "Character.hpp"

class Cure : public AMateria
{
public:
	//OCCF
	Cure	();
	Cure	(const Cure& copy);
	Cure&	operator=(const Cure& copy);
	~Cure	();

	//override
	AMateria*	clone() const;
	void		use(ICharacter& target);
};
