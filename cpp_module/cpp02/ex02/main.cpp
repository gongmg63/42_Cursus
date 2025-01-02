#include "Fixed.hpp"

int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;
	
	std::cout << Fixed::max( a, b ) << std::endl;

	// std::cout << ++(++a) << std::endl;
	// // std::cout << (a++)++ << std::endl;
	// std::cout << "a is " << a << std::endl;
	// std::cout << "b is " << b << std::endl;
	// std::cout << "+ : " << a + b << std::endl;
	// std::cout << "- : " << a - b << std::endl;
	// std::cout << "/ : " << Fixed(10) / Fixed(5) << std::endl;
	// std::cout << "> : " << (a > b) << std::endl;
	// std::cout << "< : " << (a < b) << std::endl;
	// std::cout << ">= : " << (a >= b) << std::endl;
	// std::cout << "<= : " << (a <= b) << std::endl;
	// std::cout << "== : " << (a == b) << std::endl;
	// std::cout << "!= : " << (a != b) << std::endl;
	// std::cout << "min : " << Fixed::min( a, b ) << std::endl;
	return 0;
}