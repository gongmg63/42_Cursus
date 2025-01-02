#include "Fixed.hpp"

Fixed::Fixed () 
{
	std::cout << "Default constructor called" << std::endl;
	this->num = 0;
}

Fixed::Fixed (const int num)
{
	int	fractional_bit = 1;
	int	tmp = num;

	std::cout << "Int constructor called" << std::endl;
	fractional_bit = fractional_bit << this->c_num;
	this->num = tmp * fractional_bit;
}

Fixed::Fixed (const float num)
{
	int		fractional_bit = 1;
	float	tmp = num;
	
	std::cout << "Float constructor called" << std::endl;
	fractional_bit = fractional_bit << this->c_num;
	tmp = tmp * fractional_bit;
	tmp = roundf(tmp);
	this->num = tmp;
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

std::ostream& operator<<(std::ostream &os, const Fixed& copy)
{
	os << copy.toFloat();
	return (os);
}

int	Fixed::getRawBits () const
{
	return (this->num);
}

void	Fixed::setRawBits (int const raw)
{
	this->num = raw;
}

float	Fixed::toFloat() const
{
	int		fractional_bit = 1;
	float	tmp = this->num;
	
	fractional_bit = fractional_bit << this->c_num;
	return (tmp / fractional_bit);
}

int	Fixed::toInt() const
{
	int	fractional_bit = 1;
	int	tmp = this->num;

	fractional_bit = fractional_bit << this->c_num;
	return (tmp / fractional_bit);
}

Fixed::~Fixed ()
{
	std::cout << "Destructor called" << std::endl;
}