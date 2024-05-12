#include "Fixed.hpp"

Fixed::Fixed () 
{
	std::cout << "Default constructor called" << std::endl;
	this->num = 0;
}

Fixed::Fixed (const Fixed& copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed& copy)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->num = copy.getRawBits();
	return (*this);
}

int	Fixed::getRawBits () const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->num);
}

void	Fixed::setRawBits (int const raw)
{
	this->num = raw;
}

Fixed::~Fixed ()
{
	std::cout << "Destructor called" << std::endl;
}