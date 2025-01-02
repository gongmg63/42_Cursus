#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) 
{
	Point	a(0, 0);
	Point	b(-4, 0);
	Point	c(-4, -4);
	Point	p1(-1, -0.99);
	Point	p2(0.1, 0.1);
	Point	p3(-4, -4);

	std::cout << bsp(a, b, c, p1) << std::endl;
	std::cout << bsp(b, c, a, p1) << std::endl;
	std::cout << bsp(b, a, c, p1) << std::endl;
	std::cout << bsp(a, b, c, p2) << std::endl;
	std::cout << bsp(b, c, a, p2) << std::endl;
	std::cout << bsp(b, a, c, p2) << std::endl;
	std::cout << bsp(a, b, c, p3) << std::endl;
	std::cout << bsp(b, c, a, p3) << std::endl;
	std::cout << bsp(b, a, c, p3) << std::endl;
	return 0;
}