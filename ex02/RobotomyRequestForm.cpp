#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm() 
	: AForm("", 1, 1) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& copy)
{
	(void)copy;
	return (*this);
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("RobotomyRequestForm", 72, 45) , _target(target)
{
	std::srand(std::time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
	: AForm(copy.getName(), copy.getSignGrade(), copy.getExecuteGrade()), _target(copy._target) 
{
	std::srand(std::time(NULL));
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void	RobotomyRequestForm::execute(const Bureaucrat& b) const
{
	checkExecute(b);
	std::cout << "Drilling noises...\n";
	if (std::rand() % 2 == 0) 
		std::cout << _target << " has been robotomized successfully.\n";
	else 
		std::cout << "The robotomy failed.\n";
}