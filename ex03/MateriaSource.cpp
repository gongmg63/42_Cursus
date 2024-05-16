#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; ++i)
		this->ms[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& copy)
{
	*this = copy;
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& copy)
{
	for (int i = 0; i < 4; ++i)
		this->ms[i] = copy.ms[i];
	return (*this);
}

MateriaSource::~MateriaSource() 
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->ms[i])
			delete ms[i];
	}
}

void	MateriaSource::learnMateria(AMateria* ms)
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->ms[i] == NULL)
		{
			this->ms[i] = ms;
			return ;
		}
	}
}

AMateria*	MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->ms[i] != NULL && this->ms[i]->getType() == type)
			return (this->ms[i]->clone());
	}
	return (0);
}