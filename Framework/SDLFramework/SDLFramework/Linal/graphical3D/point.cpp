#include "./point.h"
#include "../constants.h"

Linal::G3D::Point::Point() : xAxis(1), yAxis(1), zAxis(1)
{
}

Linal::G3D::Point::Point(double xAxis, double yAxis, double zAxis) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis)
{
}

Linal::G3D::Point::~Point()
{
}

Linal::G3D::Vector Linal::G3D::Point::ToVector()
{
	return Linal::G3D::Vector(xAxis, yAxis, zAxis);
}

void Linal::G3D::Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	double persX = xAxis + (sqrt(zAxis) - zAxis);
	double persY = yAxis + (sqrt(zAxis) - zAxis);
	application->DrawCircle(offsetX + (persX * Linal::FIELDWIDTH), offsetY - (persY * Linal::FIELDHEIGHT), Linal::POINTSIZE, true);
}

Linal::G3D::Vector operator*(const int & lhs, const Linal::G3D::Point & rhs)
{
	return Linal::G3D::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis, lhs * rhs.zAxis);
}
