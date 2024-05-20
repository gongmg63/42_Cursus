#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain* brain;
public:
	//OCCF
	Dog		();
	Dog		(const Dog& copy);
	Dog&	operator=(const Dog& copy);
	~Dog	();

	void		makeSound() const;
	std::string	getDogIdea() const;
	void		setDogIdea(const std::string& ideas);
};