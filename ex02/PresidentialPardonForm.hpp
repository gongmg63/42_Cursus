#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
public:
	PresidentialPardonForm	(const std::string& target);
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
	//forbidden constructor, operator
	PresidentialPardonForm	();
	PresidentialPardonForm	(const PresidentialPardonForm& copy);
	const PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);
};