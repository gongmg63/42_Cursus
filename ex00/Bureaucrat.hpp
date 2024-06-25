#pragma once

#include <iostream>
#include <exception>

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

	class GradeTooHighException : public std::exception
	{
	public:
		const char*	what() const throw() 
		{
			return ("Grade too high\n");
		}
	};
	class GradeTooLowException : public std::exception
	{
	public:
		const char*	what() const throw()
		{
			return ("Grade too low\n");
		}
	};
private:
	const std::string	_name;
	int					_grade;

	//fobidden constructor, operator
	Bureaucrat	();
	Bureaucrat	(const std::string& name);
	const Bureaucrat& operator=(const Bureaucrat& copy);
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);