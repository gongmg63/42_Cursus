#include "WrongCat.hpp"

WrongCat::WrongCat()
	:WrongAnimal()
{
	std::cout << "WrongCat default constructor called" << std::endl;
	this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& copy)
	:WrongAnimal(copy)
{
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& copy)
{
	std::cout << "WrongCat assign operator called" << std::endl;
	this->type = copy.type;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called" << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << "Mewo Mewo Mewo Mewo Mewo Mewo!" << std::endl;
}