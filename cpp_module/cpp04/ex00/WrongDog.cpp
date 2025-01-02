#include "WrongDog.hpp"

WrongDog::WrongDog()
	:WrongAnimal()
{
	std::cout << "WrongDog default constructor called" << std::endl;
	this->type = "WrongDog";
}

WrongDog::WrongDog(const WrongDog& copy)
	:WrongAnimal(copy)
{
	std::cout << "WrongDog copy constructor called" << std::endl;
}

WrongDog&	WrongDog::operator=(const WrongDog& copy)
{
	std::cout << "WrongDog assign operator called" << std::endl;
	this->type = copy.type;
	return (*this);
}

WrongDog::~WrongDog()
{
	std::cout << "WrongDog destructor called" << std::endl;
}

void	WrongDog::makeSound() const
{
	std::cout << "Bow Wow Bow Wow Bow Wow Bow Wow!" << std::endl;
}