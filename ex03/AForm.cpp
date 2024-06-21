#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, int sign_grade, int execute_grade)
	: _name(name), _sign_grade(sign_grade), _execute_grade(execute_grade), _sign(false)
{
	if (_sign_grade < 1 || _execute_grade < 1)
		throw (GradeTooHighException());
	if (_sign_grade > 150 || _execute_grade > 150)
		throw (GradeTooLowException());
}

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
		throw (Bureaucrat::GradeTooLowException());
	b.signForm(*this);
	_sign = true;
}

void	AForm::checkExecute(const Bureaucrat& b) const
{
	if (!_sign)
		throw (FormNotSignedException());
	if (_execute_grade < b.getGrade())
		throw (Bureaucrat::GradeTooLowException());
}

std::ostream& operator<<(std::ostream& os, const AForm& Aform)
{
	os << "[ " << Aform.getName() << " ]\n";
	os << "Sign grade : " << Aform.getSignGrade() << "\n";
	os << "Execute grade : " << Aform.getExecuteGrade() << "\n";
	os << "Sign : " << (Aform.getSign() ? "true" : "false");
	return (os);
}