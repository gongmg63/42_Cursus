#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm(target, 145, 137) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void	ShrubberyCreationForm::execute(const Bureaucrat& b) const
{
	checkExecute(b);
	std::ofstream ofs(getName() + "_shrubbery");

	if (!ofs)
		throw (FileOpenFail());
	
	ofs << "      ccee88oo\n";
	ofs << "  C8O8O8Q8PoOb o8oo\n";
	ofs << " dOB69QO8PdUOpugoO9bD\n";
	ofs << "CgggbU8OU qOp qOdoUOdcb\n";
	ofs << "    6OuU  /p u gcoUodpP\n";
	ofs << "      \\\\//  /douUP\n";
	ofs << "        \\\\////\n";
	ofs << "         |||/\\\n";
	ofs << "         |||\\/\n";
	ofs << "         |||||\n";
	ofs << "   .....//||||\\....\n";
	b.executeForm(*this);
}