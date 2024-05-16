#include "AMateria.hpp"
#include "Character.hpp"

AMateria::AMateria() {}

AMateria::AMateria(const AMateria& copy)
{
	*this = copy;
}

AMateria&	AMateria::operator=(const AMateria& copy)
{
	this->type = copy.type;
	return (*this);
}

AMateria::~AMateria() {}

AMateria::AMateria(std::string const& type)
{
	this->type = type;
}

std::string	const & AMateria::getType() const
{
	return (this->type);
}

void	AMateria::use(ICharacter& target)
{
	(void)target;
	std::cout << "You use just Materia..set type" << std::endl;
}

void	AMateria::setType(const std::string& type)
{
	this->type = type;
}