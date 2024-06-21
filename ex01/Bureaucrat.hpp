#pragma once

#include <iostream>
#include <exception>

class Form;

class Bureaucrat
{
public:
	Bureaucrat	(const std::string& name, int grade);	
	~Bureaucrat	();

	const std::string&	getName() const;
	int	getGrade() const;

	void	incrementGrade();
	void	decrementGrade();
	void	signForm(const Form& form) const;

	class GradeTooHighException : public std::exception
	{
	public:
		const char*	what() const throw() 
		{
			return ("Bureaucrat Grade too high\n");
		}
	};
	class GradeTooLowException : public std::exception
	{
	public:
		const char*	what() const throw()
		{
			return ("Bureaucrat Grade too low\n");
		}
	};
private:
	const std::string	_name;
	int					_grade;

	Bureaucrat	();
	Bureaucrat	(const std::string& name);
	Bureaucrat	(const Bureaucrat& copy);
	const Bureaucrat& operator=(const Bureaucrat& copy);
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);