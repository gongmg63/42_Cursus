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
        b1.signForm(sb1);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        ShrubberyCreationForm sb2("tree");
        Bureaucrat b2("b2", 145);
        b2.signForm(sb2);
        b2.executeForm(sb2);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

	try 
	{
        ShrubberyCreationForm sb3("tree");
        Bureaucrat b_tree("b_tree", 137);
        b_tree.signForm(sb3);
        b_tree.executeForm(sb3);
        std::cout << "\n";
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        RobotomyRequestForm rb("robot");
        Bureaucrat b_robot("b_robot", 45);
        b_robot.signForm(rb);
        b_robot.executeForm(rb);
        b_robot.executeForm(rb);
        std::cout << "\n";
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
	
    try 
	{
        PresidentialPardonForm pp("hihi");
        Bureaucrat b_pp("b_pp", 5);
        b_pp.signForm(pp);
        b_pp.executeForm(pp);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}