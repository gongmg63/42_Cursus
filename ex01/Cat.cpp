#include "Cat.hpp"

Cat::Cat()
	:Animal()
{
	std::cout << "Cat default constructor called" << std::endl;
	this->brain = new Brain("Cat");
	this->type = "Cat";
}

Cat::Cat(const Cat& copy)
	:Animal(copy)
{
	std::cout << "Cat copy constructor called" << std::endl;
	this->brain = new Brain("Cat");
	*this = copy;
}

Cat&	Cat::operator=(const Cat& copy)
{
	std::cout << "Cat assign operator called" << std::endl;
	this->type = copy.type;
	*(this->brain) = *(copy.brain);
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
}

void	Cat::makeSound() const
{
	std::cout << "Mewo Mewo Mewo Mewo Mewo Mewo!" << std::endl;
}

std::string	Cat::getCatIdea() const
{
	return (this->brain->getIdeas());
}

void	Cat::setCatIdea(const std::string& ideas)
{
	this->brain->setIdeas(ideas);
}