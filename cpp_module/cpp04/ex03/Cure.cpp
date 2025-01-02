#include "Cure.hpp"

Cure::Cure()
	:AMateria("cure") {}

Cure::Cure(const Cure& copy)
	:AMateria(copy)
{
	*this = copy;
}

Cure&	Cure::operator=(const Cure& copy)
{
	this->type = copy.type;
	return (*this);
}

Cure::~Cure() {}

AMateria*	Cure::clone() const
{
	AMateria*	tmp = new Cure();
	
	tmp->setType(this->type);
	return (tmp);
}

void	Cure::use(ICharacter& target)
{
	if (this->type == "cure")
		std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
	else
		std::cout << "You cast cure, but type is " << this->type << std::endl;
}