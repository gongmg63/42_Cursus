#pragma once

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
public:
	ShrubberyCreationForm	(const std::string& target);
	~ShrubberyCreationForm	();

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
	ShrubberyCreationForm	();
	ShrubberyCreationForm	(const ShrubberyCreationForm& copy);
	const ShrubberyCreationForm& operator=(const ShrubberyCreationForm& copy);
};