#include "./vector.h"
#include "../constants.h"

Linal::G3D::Vector::Vector() : xAxis(0), yAxis(0), startingX(0), startingY(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G3D::Vector::Vector(double xAxis, double yAxis, double zAxis) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis), startingX(0), startingY(0), startingZ(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G3D::Vector::Vector(double xAxis, double yAxis, double zAxis, double xOrigin, double yOrigin, double zOrigin) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis), startingX(xOrigin), startingY(yOrigin), startingZ(zOrigin)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G3D::Vector::~Vector()
{
}

Linal::G3D::Vector Linal::G3D::Vector::operator+(const Linal::G3D::Vector & rhs)
{
	return Vector(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis, startingX, startingY, startingZ);
}

Linal::G3D::Vector& Linal::G3D::Vector::operator+=(const Linal::G3D::Vector & rhs)
{
	this->xAxis += rhs.xAxis;
	this->yAxis += rhs.yAxis;
	this->zAxis += rhs.zAxis;
	return *this;
}

Linal::G3D::Vector Linal::G3D::Vector::operator-(const Linal::G3D::Vector & rhs)
{
	return Linal::G3D::Vector(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis, startingX, startingY, startingZ);
}

Linal::G3D::Vector& Linal::G3D::Vector::operator-=(const Linal::G3D::Vector & rhs)
{
	this->xAxis -= rhs.xAxis;
	this->yAxis -= rhs.yAxis;
	return *this;
}

Linal::G3D::Vector Linal::G3D::Vector::operator*(const double & rhs)
{
	return Linal::G3D::Vector(xAxis * rhs, yAxis * rhs, zAxis * rhs, startingX, startingY, startingZ);
}

Linal::G3D::Vector Linal::G3D::Vector::operator*(const Linal::G3D::Vector & rhs)
{
	return Linal::G3D::Vector(xAxis * rhs.xAxis, yAxis * rhs.yAxis, zAxis * rhs.zAxis, startingX, startingY, startingZ);
}

Linal::G3D::Vector Linal::G3D::Vector::operator/(const double & rhs)
{
	return Linal::G3D::Vector(xAxis / rhs, yAxis / rhs, zAxis / rhs, startingX, startingY, startingZ);
}

Linal::G3D::Vector Linal::G3D::Vector::operator/(const Linal::G3D::Vector & rhs)
{
	return Linal::G3D::Vector(xAxis / rhs.xAxis, yAxis / rhs.yAxis, zAxis / rhs.zAxis, startingX, startingY, startingZ);
}

Linal::G3D::Point Linal::G3D::Vector::ToPoint()
{
	return Point(xAxis, yAxis, zAxis);
}

void Linal::G3D::Vector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	offsetX += ((startingX + (sqrt(startingZ) - startingZ)) * Linal::FIELDWIDTH);
	offsetY -= ((startingY + (sqrt(startingZ) - startingZ)) * Linal::FIELDHEIGHT);
	application->SetColor(Color(255, 0, 0, 255));
	application->DrawLine(offsetX, offsetY, offsetX + ((xAxis + (sqrt(zAxis) - zAxis)) * Linal::FIELDWIDTH), offsetY - ((yAxis + (sqrt(zAxis) - zAxis)) * Linal::FIELDHEIGHT));
}

Color Linal::G3D::Vector::GetColor()
{
	return myColor;
}

Linal::G3D::Vector operator*(const double & lhs, const Linal::G3D::Vector & rhs)
{
	return Linal::G3D::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis, lhs * rhs.xAxis);
}
