#include "Ice.hpp"

Ice::Ice()
	:AMateria("ice") {}

Ice::Ice(const Ice& copy)
	:AMateria(copy)
{
	*this = copy;
}

Ice&	Ice::operator=(const Ice& copy)
{
	this->type = copy.type;
	return (*this);
}

Ice::~Ice() {}

AMateria*	Ice::clone() const
{
	return (new Ice());
}

void	Ice::use(ICharacter& target)
{
	if (this->type == "ice")
		std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
	else
		std::cout << "You cast Ice, but type isn't Ice.." << std::endl;
}