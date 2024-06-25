#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
public:
	PresidentialPardonForm	(const std::string& target);
	PresidentialPardonForm	(const PresidentialPardonForm& copy);
	~PresidentialPardonForm	();

	void	execute(const Bureaucrat& b) const;
private:
	std::string _target;
	
	//forbidden constructor, operator
	PresidentialPardonForm	();
	PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);
};