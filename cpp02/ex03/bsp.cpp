#include "Point.hpp"

Fixed	cal_outer(const Point p, const Point a, const Point b)
{
	Fixed	out;
	Point	ab(b.getXValue().toFloat() - a.getXValue().toFloat(),\
				b.getYValue().toFloat() - a.getYValue().toFloat());
	Point	ap(p.getXValue().toFloat() - a.getXValue().toFloat(),\
				p.getYValue().toFloat() - a.getYValue().toFloat());

	out.setRawBits(ab.getXValue().getRawBits() * ap.getYValue().getRawBits() - \
					ab.getYValue().getRawBits() * ap.getXValue().getRawBits());
	return (out);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	out1, out2, out3;

	out1 = cal_outer(point, a, b);
	out2 = cal_outer(point, b, c);
	out3 = cal_outer(point, c, a);
	if ((out1.getRawBits() > 0 && out2.getRawBits() > 0 && out3.getRawBits() > 0) ||\
		(out1.getRawBits() < 0 && out2.getRawBits() < 0 && out3.getRawBits() < 0))
		return (true);
	return (false);
}