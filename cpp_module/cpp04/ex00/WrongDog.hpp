#pragma once
#include "WrongAnimal.hpp"

class WrongDog : public WrongAnimal
{
public:
	//OCCF
	WrongDog		();
	WrongDog		(const WrongDog& copy);
	WrongDog&	operator=(const WrongDog& copy);
	~WrongDog	();

	void makeSound() const;
};