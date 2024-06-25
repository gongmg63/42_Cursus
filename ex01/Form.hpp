#pragma once

#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
public:
	Form	(const std::string& name, int sign_grade, int execute_grade);
	Form	(const Form& copy);
	~Form	();

	const std::string&	getName() const;
	int		getSignGrade() const;
	int 	getExecuteGrade() const;
	bool	getSign() const;

	void	beSigned(const Bureaucrat& b);

	//nested class
	class GradeTooHighException : public std::exception
	{
	public:
		const char*	what() const throw() 
		{
			return ("Form Grade too high\n");
		}
	};
	class GradeTooLowException : public std::exception
	{
	public:
		const char*	what() const throw()
		{
			return ("Form Grade too low\n");
		}
	};
private:
	const std::string	_name;
	const int			_sign_grade;
	const int			_execute_grade;
	bool				_sign;
	
	//forbidden constructor, operator
	Form	();
	Form	(const std::string& name);
	Form	(const std::string& name, const int sign_grade);
	const Form&	operator=(const Form& copy);
};

std::ostream& operator<<(std::ostream& os, const Form& form);