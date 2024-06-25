#pragma once

#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
public:
	AForm	(const std::string& name, int sign_grade, int execute_grade);
	AForm	(const AForm& copy);
	virtual ~AForm	();

	const std::string&	getName() const;
	int		getSignGrade() const;
	int 	getExecuteGrade() const;
	bool	getSign() const;

	void	beSigned(const Bureaucrat& b);
	void	checkExecute(const Bureaucrat& b) const;
	virtual void	execute(const Bureaucrat& b) const = 0;

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
	class FormNotSignedException : public std::exception
	{
	public:
		const char* what() const throw()
		{
			return ("Form isn't signed\n");
		}
	};
private:
	const std::string	_name;
	const int			_sign_grade;
	const int			_execute_grade;
	bool				_sign;
	
	//forbidden constructor, operator
	AForm	();
	AForm	(const std::string& name);
	AForm	(const std::string& name, const int sign_grade);
	const AForm&	operator=(const AForm& copy);
};

std::ostream& operator<<(std::ostream& os, const AForm& Aform);