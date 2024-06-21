#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	try 
	{
        Intern someRandomIntern;
        AForm* rrf;
        Bureaucrat b("hihi", 1);

        rrf = someRandomIntern.makeForm("shrubbery creation", "John");
        rrf->beSigned(b);
        rrf->execute(b);
        std::cout << "\n";
        delete rrf;

        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        rrf->beSigned(b);
        rrf->execute(b);
        std::cout << "\n";
        delete rrf;
        
        rrf = someRandomIntern.makeForm("presidential pardon", "Jenny");
        rrf->beSigned(b);
        rrf->execute(b);
        std::cout << "\n";
        delete rrf;

        rrf = someRandomIntern.makeForm("unexist form", "Hi");
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
}