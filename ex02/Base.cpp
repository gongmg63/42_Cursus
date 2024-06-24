#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base*	generate(void)
{
	int	random;

	std::srand(std::time(NULL));
	random = rand() % 3;
	if (random == 0)
		return (new A());
	if (random == 1)
		return (new B());
	return (new C());
}

void	identify(Base* p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "Pointer A\n";
	if (dynamic_cast<B *>(p))
		std::cout << "Pointer B\n";
	if (dynamic_cast<C *>(p))
		std::cout << "Pointer C\n";
}

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "Reference A\n";
	}
	catch(const std::exception& e)	{};
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "Reference B\n";
	}
	catch(const std::exception& e)	{};
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "Reference C\n";
	}
	catch(const std::exception& e)	{};	
}