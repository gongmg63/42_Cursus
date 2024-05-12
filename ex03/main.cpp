#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) 
{
	Point	a(0, 0);
	Point	b(-4, 0);
	Point	c(-4, -4);
	Point	p(-1, -0.99);

	std::cout << bsp(a, b, c, p) << std::endl;
	return 0;
}