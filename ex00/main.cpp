#include "Bureaucrat.hpp"

int main()
{
	try 
	{
        Bureaucrat b1("Alice", 0);
    } 
	catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    try 
	{
        Bureaucrat b2("Bob", 151);
    } 
	catch (const std::exception& e) 
	{
        std::cout << "Exception: " << e.what() << "\n";
    }

    try {
        Bureaucrat b3("Charlie", 150);
        std::cout << b3.getName() << " created with grade " << b3.getGrade() << "\n";
		b3.decrementGrade();
    }
	catch (const std::exception& e) 
	{
        std::cout << "Exception: " << e.what() << "\n";
    }

    try {
        Bureaucrat b4("Jhon", 1);
        std::cout << b4.getName() << " created with grade " << b4.getGrade() << "\n";
		b4.incrementGrade();
    }
	catch (const std::exception& e) 
	{
        std::cout << "Exception: " << e.what() << "\n";
    }
}