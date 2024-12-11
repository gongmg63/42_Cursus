#include "Base.hpp"

int main()
{
	Base*	random = generate();

	identify(random);
	identify(*random);
}