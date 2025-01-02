#pragma once
#include "Animal.hpp"

class Cat : public Animal
{
public:
	//OCCF
	Cat		();
	Cat		(const Cat& copy);
	Cat&	operator=(const Cat& copy);
	~Cat	();

	void makeSound() const;
};