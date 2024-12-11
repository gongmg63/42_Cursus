#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal default constructor called" << std::endl;
	this->type = "Animal";
}

Animal::Animal(const Animal& copy)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = copy;
}

Animal&	Animal::operator=(const Animal &copy)
{
	std::cout << "Animal assign operator called" << std::endl;
	this->type = copy.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const std::string type)
{
	this->type = type;
}

std::string	Animal::getType() const
{
	return (this->type);
}