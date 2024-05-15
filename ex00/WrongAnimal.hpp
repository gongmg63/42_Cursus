#pragma once
#include <iostream>

class WrongAnimal
{
protected:
	std::string	type;
public:
	//OCCF
	WrongAnimal	();
	WrongAnimal	(const WrongAnimal& copy);
	WrongAnimal&	operator=(const WrongAnimal& copy);
	virtual ~WrongAnimal	();

	WrongAnimal	(const std::string type);

	std::string		getType() const;
	//virtual 이 선언되어 있이 않은 경우
	void			makeSound() const;
};
