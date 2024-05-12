#pragma once
#include "Fixed.hpp"

class Point
{
private:
	const Fixed x;
	const Fixed y;
public:
	Point	();
	Point	(const float x, const float y);
	Point	(const Point& copy);
	Point&	operator=(const Point& copy);
	~Point	();
	Fixed	getXValue() const;
	Fixed	getYValue() const;
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);
Fixed	cal_outer(const Point p, const Point a, const Point b);