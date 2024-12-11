#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() 
	: _sign_grade(1), _execute_grade(1) {}

AForm&	AForm::operator=(const AForm& copy)
{
	(void)copy;
	return (*this);
}

AForm::AForm(const std::string& name, int sign_grade, int execute_grade)
	: _name(name), _sign_grade(sign_grade), _execute_grade(execute_grade), _sign(false)
{
	if (_sign_grade < 1 || _execute_grade < 1)
		throw (GradeTooHighException());
	if (_sign_grade > 150 || _execute_grade > 150)
		throw (GradeTooLowException());
}

AForm::AForm(const AForm& copy)
	: _name(copy._name), _sign_grade(copy._sign_grade), _execute_grade(copy._execute_grade), _sign(copy._sign) {}

AForm::~AForm() {}

const std::string& AForm::getName() const
{
	return (_name);
}

int	AForm::getSignGrade() const
{
	return (_sign_grade);
}

int AForm::getExecuteGrade() const
{
	return (_execute_grade);
}

bool	AForm::getSign() const
{
	return (_sign);
}

void	AForm::beSigned(const Bureaucrat& b)
{
	if (_sign_grade < b.getGrade())
		throw (GradeTooLowException());
	if (_sign)
	{
		std::cout  << b.getName() << " couldn't sign " << _name << " because " << _name << " aleady signed.\n";
		return ;
	}
	_sign = true;
	std::cout << b.getName() << " signed " << _name << "\n";
}

void	AForm::checkExecute(const Bureaucrat& b) const
{
	if (!_sign)
		throw (FormNotSignedException());
	if (_execute_grade < b.getGrade())
		throw (GradeTooLowException());
}

const char*	AForm::GradeTooHighException::what() const throw()
{
	return ("Form Grade too high\n");
}

const char*	AForm::GradeTooLowException::what() const throw()
{
	return ("Form Grade too low\n");
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return ("Form isn't signed\n");
}

std::ostream& operator<<(std::ostream& os, const AForm& Aform)
{
	os << "[ " << Aform.getName() << " ]\n";
	os << "Sign grade : " << Aform.getSignGrade() << "\n";
	os << "Execute grade : " << Aform.getExecuteGrade() << "\n";
	os << "Sign : " << (Aform.getSign() ? "true" : "false");
	return (os);
}