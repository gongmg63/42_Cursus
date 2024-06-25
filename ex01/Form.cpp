#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int sign_grade, int execute_grade)
	: _name(name), _sign_grade(sign_grade), _execute_grade(execute_grade), _sign(false)
{
	if (_sign_grade < 1 || _execute_grade < 1)
		throw (GradeTooHighException());
	if (_sign_grade > 150 || _execute_grade > 150)
		throw (GradeTooLowException());
}

Form::Form(const Form& copy)
	: _name(copy._name), _sign_grade(copy._sign_grade), _execute_grade(copy._execute_grade), _sign(copy._sign) {}

Form::~Form() {}

const std::string& Form::getName() const
{
	return (_name);
}

int	Form::getSignGrade() const
{
	return (_sign_grade);
}

int Form::getExecuteGrade() const
{
	return (_execute_grade);
}

bool	Form::getSign() const
{
	return (_sign);
}

void	Form::beSigned(const Bureaucrat& b)
{
	if (_sign_grade < b.getGrade())
		throw (Form::GradeTooLowException());
	b.signForm(*this);
	_sign = true;
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "[ " << form.getName() << " ]\n";
	os << "Sign grade : " << form.getSignGrade() << "\n";
	os << "Execute grade : " << form.getExecuteGrade() << "\n";
	os << "Sign : " << (form.getSign() ? "true" : "false");
	return (os);
}