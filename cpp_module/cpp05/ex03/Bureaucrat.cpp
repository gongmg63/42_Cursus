#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() {}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& copy) 
{
	(void)(copy);
	return (*this);
}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: _name(name), _grade(grade) 
{
	if (_grade > 150)
		throw GradeTooLowException();
	if (_grade < 1)
		throw GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
	: _name(copy._name), _grade(copy._grade) {}

Bureaucrat::~Bureaucrat() {}

const std::string&	Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade() const
{
	return (_grade);
}

void	Bureaucrat::incrementGrade()
{
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	_grade--;
}

void	Bureaucrat::decrementGrade()
{
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	_grade++;
}

void	Bureaucrat::signForm(AForm& form)
{
	form.beSigned(*this);
}

void Bureaucrat::executeForm(const AForm& form) const
{
	form.execute(*this);
	std::cout << _name << " executed " << form.getName() << "\n";
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat Grade too high\n");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat Grade too low\n");
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade();
	return (os);
}