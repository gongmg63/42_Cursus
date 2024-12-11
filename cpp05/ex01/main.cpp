#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try 
	{
        Form f1("Form 1", 151, 150);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

	try 
	{
        Form f2("Form 2", 0, 150);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

	try 
	{
        Form f3("Form 3", 1, 150);
        Bureaucrat b1("b1", 2);
        std::cout << f3 << "\n";
        std::cout << b1 << "\n";
        f3.beSigned(b1);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    try {
        Form f4("Form 4", 3, 150);
        Bureaucrat b2("b2", 2);
        std::cout << f4 << "\n";
        std::cout << b2 << "\n";
        b2.signForm(f4);
        std::cout << f4 << "\n";
        b2.signForm(f4);
    }
	catch (const std::exception& e) 
	{
        std::cout << "Exception: " << e.what() << "\n";
    }
}