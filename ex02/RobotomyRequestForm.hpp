#pragma once

#include "AForm.hpp"
#include <ctime>
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
public:
	RobotomyRequestForm	(const std::string& target);
	RobotomyRequestForm	(const RobotomyRequestForm& copy);
	~RobotomyRequestForm	();

	void	execute(const Bureaucrat& b) const;

	class FileOpenFail : public std::exception
	{
	public:
		const char*	what() const throw() 
		{
			return ("File open fail\n");
		}
	};
private:
	std::string _target;

	//forbidden constructor, operator
	RobotomyRequestForm	();
	const RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);
};