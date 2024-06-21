#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	try 
	{
        ShrubberyCreationForm sb1("tree");
        Bureaucrat b1("b1", 146);
        sb1.beSigned(b1);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        ShrubberyCreationForm sb2("tree");
        Bureaucrat b2("b2", 145);
        sb2.beSigned(b2);
        sb2.execute(b2);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

	try 
	{
        ShrubberyCreationForm sb3("tree");
        Bureaucrat b3("b3", 137);
        sb3.beSigned(b3);
        sb3.execute(b3);
        std::cout << "\n";
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        RobotomyRequestForm rb("robot");
        Bureaucrat b_robot("b_robot", 45);
        rb.beSigned(b_robot);
        rb.execute(b_robot);
        rb.execute(b_robot);
        std::cout << "\n";
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        PresidentialPardonForm pp("hihi");
        Bureaucrat b_pp("b_pp", 5);
        pp.beSigned(b_pp);
        pp.execute(b_pp);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}