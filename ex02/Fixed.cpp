#include "Fixed.hpp"

Fixed::Fixed () 
{
	this->num = 0;
}

Fixed::Fixed (const int num)
{
	int	fractional_bit = 1;
	int	tmp = num;

	fractional_bit = fractional_bit << this->c_num;
	this->num = tmp * fractional_bit;
}

Fixed::Fixed (const float num)
{
	int		fractional_bit = 1;
	float	tmp = num;
	
	fractional_bit = fractional_bit << this->c_num;
	tmp = tmp * fractional_bit;
	tmp = roundf(tmp);
	this->num = tmp;
}

Fixed::Fixed (const Fixed& copy)
{
	*this = copy;
}

Fixed::~Fixed () {}

Fixed& Fixed::operator=(const Fixed& copy)
{
	this->num = copy.getRawBits();
	return (*this);
}

Fixed	Fixed::operator+(const Fixed& copy) const
{
	Fixed	ret(*this);

	ret.num += copy.getRawBits();
	return (ret);
}

Fixed	Fixed::operator-(const Fixed& copy) const
{
	Fixed	ret(*this);

	ret.num -= copy.getRawBits();
	return (ret);
}

Fixed	Fixed::operator*(const Fixed& copy) const
{
	Fixed	ret(*this);
	int		fractional_bit = 1;

	fractional_bit = fractional_bit << this->c_num;
	ret.num *= copy.getRawBits() / fractional_bit;
	return (ret);
}

Fixed	Fixed::operator/(const Fixed& copy) const
{
	Fixed	ret(*this);
	int		fractional_bit = 1;

	fractional_bit = fractional_bit << this->c_num;
	ret.num /= copy.getRawBits() / fractional_bit;
	return (ret);
}

const Fixed	Fixed::operator++(int)
{
	const Fixed	ret(*this);

	this->num++;
	return (ret);
}

Fixed&	Fixed::operator++(void)
{
	this->num++;
	return (*this);
}

const Fixed	Fixed::operator--(int)
{
	Fixed	ret(*this);

	this->num--;
	return (ret);
}

Fixed&	Fixed::operator--(void)
{
	this->num--;
	return (*this);
}

bool	Fixed::operator>(const Fixed& copy) const
{
	if (this->getRawBits() > copy.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator<(const Fixed& copy) const
{
	if (this->getRawBits() < copy.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator>=(const Fixed& copy) const
{
	if (this->getRawBits() >= copy.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator<=(const Fixed& copy) const
{
	if (this->getRawBits() <= copy.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator==(const Fixed& copy) const
{
	if (this->getRawBits() == copy.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator!=(const Fixed& copy) const
{
	if (this->getRawBits() != copy.getRawBits())
		return (true);
	return (false);
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
	float	tmp = this->getRawBits();
	
	fractional_bit = fractional_bit << this->c_num;
	return (tmp / fractional_bit);
}

int	Fixed::toInt() const
{
	int	fractional_bit = 1;
	int	tmp = this->getRawBits();

	fractional_bit = fractional_bit << this->c_num;
	return (tmp / fractional_bit);
}

const Fixed&	Fixed::min(Fixed& first, Fixed& second)
{
	if (first.num > second.num)
		return (second);
	return (first);
}

const Fixed&	Fixed::min(const Fixed& first, const Fixed& second)
{
	if (first.num > second.num)
		return (second);
	return (first);
}

const Fixed&	Fixed::max(Fixed& first, Fixed& second)
{
	if (first.num < second.num)
		return (second);
	return (first);
}

const Fixed&	Fixed::max(const Fixed& first, const Fixed& second)
{
	if (first.num < second.num)
		return (second);
	return (first);
}

std::ostream& operator<<(std::ostream &os, const Fixed& copy)
{
	os << copy.toFloat();
	return (os);
}