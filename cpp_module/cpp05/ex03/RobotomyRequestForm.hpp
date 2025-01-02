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
private:
	std::string _target;

	//forbidden constructor, operator
	RobotomyRequestForm	();
	RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);
};