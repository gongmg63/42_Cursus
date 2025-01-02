#pragma once
#include <iostream>

class ICharacter;

class AMateria
{
protected:
	std::string	type;
public:
	//OCCF
	AMateria			();
	AMateria			(const AMateria& copy);
	AMateria&			operator=(const AMateria& copy);
	virtual ~AMateria	();

	//constructor
	AMateria(std::string const & type);

	//subject function
	std::string const & getType() const; //Returns the materia type
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);

	//member function
	void	setType(const std::string& type);
};