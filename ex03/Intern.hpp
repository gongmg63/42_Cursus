#pragma once

#include "AForm.hpp"

class Intern
{
public:
	Intern	();
	Intern	(const Intern& copy);
	const Intern&	operator=(const Intern& copy);
	~Intern	();

	AForm*	makeForm(const std::string& form, const std::string& target);

	AForm*	createShrubbery(const std::string& target);
	AForm*	createRobotomy(const std::string& target);
	AForm*	createPardon(const std::string& target);
	class NoFormException : public std::exception
	{
	public:
		const char* what() const throw()
		{
			return ("Doesn't exist that form\n");
		}
	};
private:
	std::string _form_list[3];
	AForm *(Intern::*_create_form[3])(const std::string& target);
};