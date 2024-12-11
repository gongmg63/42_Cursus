#pragma once
#include <iostream>

class Brain
{
private:
	std::string ideas[100];
public:
	//OCCF
	Brain	();
	Brain	(const Brain& copy);
	Brain&	operator=(const Brain& copy);
	~Brain	();

	Brain	(const std::string& ideas);
	
	void		setIdeas(const std::string& ideas);
	std::string	getIdeas() const;
};
