#pragma once
#include <iostream>

class Animal
{
protected:
	std::string	type;
public:
	//OCCF
	Animal	();
	Animal	(const Animal& copy);
	Animal&	operator=(const Animal& copy);
	virtual ~Animal	();

	Animal	(const std::string type);

	std::string		getType() const;
	virtual	void	makeSound() const;
};
