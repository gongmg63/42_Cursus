#include "Point.hpp"

Point::Point ()
	: x(0), y(0)
{
}

Point::Point (const float x, const float y)
	: x(x), y(y)
{
}

Point::Point (const Point& copy)
	: x(copy.x), y(copy.y)
{
}

Point& Point::operator=(const Point& copy)
{
	(void)copy;
	return (*this);
}

Point::~Point() {}

Fixed	Point::getXValue() const
{
	return (this->x);
}

Fixed	Point::getYValue() const
{
	return (this->y);
}