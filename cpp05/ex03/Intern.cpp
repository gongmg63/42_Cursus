#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

std::string Intern::_form_list[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
AForm* (Intern::*Intern::_create_form[3])(const std::string& target) = {
    &Intern::createShrubbery,
    &Intern::createRobotomy,
    &Intern::createPardon
};

Intern::Intern() {}

Intern::Intern(const Intern& copy)
{
	*this = copy;
}

const Intern&	Intern::operator=(const Intern& copy)
{
	for (int i = 0; i < 3; ++i)
	{
		_form_list[i] = copy._form_list[i];
		_create_form[i] = copy._create_form[i];
	}
	return (*this);
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

const char*	Intern::NoFormException::what() const throw()
{
	return ("Doesn't exist that form\n");
}