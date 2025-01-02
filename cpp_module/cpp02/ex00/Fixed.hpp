#pragma once
#include <iostream>

class Fixed
{
private:
	static const int c_num = 8;
	int	num;
public:
	Fixed	();
	Fixed	(const Fixed& copy);
	Fixed&	operator=(const Fixed& copy);
	~Fixed	();
	int		getRawBits () const;
	void	setRawBits (int const raw);
};