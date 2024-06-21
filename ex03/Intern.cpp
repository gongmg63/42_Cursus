#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
	_form_list[0] = "shrubbery creation";
	_form_list[1] = "robotomy request";
	_form_list[2] = "presidential pardon";
    _create_form[0] = &Intern::createShrubbery;
    _create_form[1] = &Intern::createRobotomy;
    _create_form[2] = &Intern::createPardon;
}

Intern::~Intern() {}

AForm*	Intern::createShrubbery(const std::string& target)
{
	return (new ShrubberyCreationForm(target));
}

AForm*	Intern::createRobotomy(const std::string& target)
{
	return (new RobotomyRequestForm(target));
}

AForm*	Intern::createPardon(const std::string& target)
{
	return (new PresidentialPardonForm(target));
}

AForm*	Intern::makeForm(const std::string& form, const std::string& target)
{
	for (int i = 0; i < 3; ++i)
	{
		if (_form_list[i] == form)
		{
			std::cout << "Intern creates " << form << "\n";
			return ((this->*_create_form[i])(target));
		}
	}
	throw (NoFormException());
}