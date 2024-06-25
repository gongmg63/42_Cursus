#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
public:
	PresidentialPardonForm	(const std::string& target);
	PresidentialPardonForm	(const PresidentialPardonForm& copy);
	~PresidentialPardonForm	();

	void	execute(const Bureaucrat& b) const;

	class FileOpenFail : public std::exception
	{
	public:
		const char*	what() const throw() 
		{
			return ("File open fail\n");
		}
	};
private:
	std::string _target;
	
	//forbidden constructor, operator
	PresidentialPardonForm	();
	const PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);
};