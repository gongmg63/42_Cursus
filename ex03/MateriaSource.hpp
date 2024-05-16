#pragma once
#include <iostream>
#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class	AMateria;

class MateriaSource : public IMateriaSource
{
private:
	AMateria *ms[4];
public:
	//OCCF
	MateriaSource	();
	MateriaSource	(const MateriaSource& copy);
	MateriaSource&	operator=(const MateriaSource& copy);
	~MateriaSource	();

	//override
	void		learnMateria(AMateria*);
	AMateria*	createMateria(std::string const & type);
};
