#include "Cat.hpp"

Cat::Cat()
	:Animal()
{
	std::cout << "Cat default constructor called" << std::endl;
	this->type = "Cat";
}

Cat::Cat(const Cat& copy)
	:Animal(copy)
{
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat&	Cat::operator=(const Cat& copy)
{
	std::cout << "Cat assign operator called" << std::endl;
	this->type = copy.type;
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Mewo Mewo Mewo Mewo Mewo Mewo!" << std::endl;
}