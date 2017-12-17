#include "point.h"
#include "../constants.h"

using namespace Linal::G3D;

Point::Point() : xAxis(1), yAxis(1), zAxis(1)
{
}

Point::Point(double xAxis, double yAxis, double zAxis) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis)
{
}

Point::~Point()
{
}

Vector Point::ToVector()
{
	return Vector(xAxis, yAxis, zAxis);
}

void Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT), Linal::POINTSIZE, true);
}

Vector operator*(const int & lhs, const Point & rhs)
{
	return Vector(lhs * rhs.xAxis, lhs * rhs.yAxis, lhs * rhs.zAxis);
}
