#pragma once

#include <iostream>
#include <exception>

class AForm;

class Bureaucrat
{
public:
	Bureaucrat	(const std::string& name, int grade);	
	Bureaucrat	(const Bureaucrat& copy);
	~Bureaucrat	();

	const std::string&	getName() const;
	int	getGrade() const;

	void	incrementGrade();
	void	decrementGrade();
	void	signForm(AForm& form);
	void	executeForm(const AForm& form) const;

	class GradeTooHighException : public std::exception
	{
	public:
		const char*	what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public:
		const char*	what() const throw();
	};
private:
	const std::string	_name;
	int					_grade;

	//fobidden constructor, operator
	Bureaucrat	();
	Bureaucrat& operator=(const Bureaucrat& copy);
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);