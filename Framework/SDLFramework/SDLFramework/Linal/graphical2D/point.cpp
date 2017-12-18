#include "./point.h"
#include "../constants.h"

Linal::G2D::Point::Point() : xAxis(1), yAxis(1)
{
}

Linal::G2D::Point::Point(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
}

Linal::G2D::Point::~Point()
{
}

Linal::G2D::Vector Linal::G2D::Point::ToVector()
{
	return Linal::G2D::Vector(xAxis, yAxis);
}

void Linal::G2D::Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT), Linal::POINTSIZE, true);
}

Linal::G2D::Vector operator*(const int & lhs, const Linal::G2D::Point & rhs)
{
	return Linal::G2D::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis);
}
