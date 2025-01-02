#include "Dog.hpp"

Dog::Dog()
	:Animal()
{
	std::cout << "Dog default constructor called" << std::endl;
	this->brain = new Brain("Dog");
	this->type = "Dog";
}

Dog::Dog(const Dog& copy)
	:Animal(copy)
{
	std::cout << "Dog copy constructor called" << std::endl;
	this->brain = new Brain("Dog");
	*this = copy;
}

Dog&	Dog::operator=(const Dog& copy)
{
	std::cout << "Dog assign operator called" << std::endl;
	this->type = copy.type;
	*(this->brain) = *(copy.brain);
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->brain;
}

void	Dog::makeSound() const
{
	std::cout << "Bow Wow Bow Wow Bow Wow Bow Wow!" << std::endl;
}

std::string	Dog::getDogIdea() const
{
	return (this->brain->getIdeas());
}

void	Dog::setDogIdea(const std::string& ideas)
{
	this->brain->setIdeas(ideas);
}