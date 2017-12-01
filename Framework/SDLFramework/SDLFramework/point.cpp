#include "point.h"
#include "constants.h"

Linal::Point::Point() : xAxis(1), yAxis(1)
{
}

Linal::Point::Point(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
}

Linal::Point::~Point()
{
}

Linal::Vector Linal::Point::ToVector()
{
	return Vector(xAxis, yAxis);
}

void Linal::Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT), Point::SIZE, true);
}

Linal::Vector operator*(const int & lhs, const Linal::Point & rhs)
{
	return Linal::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis);
}
