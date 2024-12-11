#pragma once
#include <iostream>
#include <cmath>

class Fixed
{
private:
	static const int c_num = 8;
	int	num;
public:
	Fixed	();
	Fixed	(const Fixed& copy);
	Fixed	(const int num);
	Fixed	(const float num);
	Fixed&	operator=(const Fixed& copy);
	~Fixed	();
	int		getRawBits () const;
	void	setRawBits (int const raw);
	float	toFloat () const;
	int		toInt () const;
};

std::ostream&	operator<<(std::ostream &os, const Fixed& copy);
