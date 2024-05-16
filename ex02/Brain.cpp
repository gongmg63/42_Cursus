#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain& copy)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = copy;
}

Brain&	Brain::operator=(const Brain& copy)
{
	std::cout << "Brain assign operator called" << std::endl;
	for (int i = 0; i < 100; ++i)
		this->ideas[i] = copy.ideas[i];
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called, Ideas : " << this->getIdeas() << std::endl;
}

Brain::Brain(const std::string& ideas)
{
	std::cout << "Brain constructor with attribute called" << std::endl;
	for (int i = 0; i < 100; ++i)
		this->ideas[i] = ideas;
}

void	Brain::setIdeas(const std::string& ideas)
{
	std::cout << "Brain set ideas called" << std::endl;
	for (int i = 0; i < 100; ++i)
		this->ideas[i] = ideas;
}

std::string Brain::getIdeas() const
{
	return (this->ideas[0]);
}