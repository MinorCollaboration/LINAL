#include "point.h"
#include "constants.h"

using namespace Linal::G2D;

Point::Point() : xAxis(1), yAxis(1)
{
}

Point::Point(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
}

Point::~Point()
{
}

Vector Point::ToVector()
{
	return Vector(xAxis, yAxis);
}

void Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT), Point::SIZE, true);
}

Vector operator*(const int & lhs, const Point & rhs)
{
	return Vector(lhs * rhs.xAxis, lhs * rhs.yAxis);
}
