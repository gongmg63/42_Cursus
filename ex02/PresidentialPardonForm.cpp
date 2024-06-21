#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
	: AForm(target, 25, 5) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

void	PresidentialPardonForm::execute(const Bureaucrat& b) const
{
	checkExecute(b);

	std::cout << getName() << " has been pardoned by Zaphod Beeblebrox.\n";
	b.executeForm(*this);
}