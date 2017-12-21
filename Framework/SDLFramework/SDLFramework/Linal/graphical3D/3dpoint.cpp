#include "./3dpoint.h"
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
	double sqrtZ = (zAxis < 0) ? -sqrt(+zAxis) * 2 : sqrt(zAxis) * 2;

	double finalXAxis = xAxis + (sqrtZ - zAxis);
	double finalYAxis = yAxis + (sqrtZ - zAxis);

	application->DrawCircle(offsetX + (finalXAxis * Linal::FIELDWIDTH), offsetY - (finalYAxis * Linal::FIELDHEIGHT), Linal::POINTSIZE, true);
}

Linal::G3D::Vector operator*(const int & lhs, const Linal::G3D::Point & rhs)
{
	return Linal::G3D::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis, lhs * rhs.zAxis);
}
