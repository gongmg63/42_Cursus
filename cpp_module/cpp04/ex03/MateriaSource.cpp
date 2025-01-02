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
	std::cout << "Can't learn materia. It's full" << std::endl;
}

AMateria*	MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; ++i)
	{
		if (this->ms[i] && this->ms[i]->getType() == type)
			return (this->ms[i]->clone());
	}
	std::cout << "Can't create materia. There's no " << type << std::endl;
	return (0);
}