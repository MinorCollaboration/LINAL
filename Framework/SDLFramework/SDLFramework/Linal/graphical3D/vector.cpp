#include "vector.h"
#include "../constants.h"

using namespace Linal::G3D;

Vector::Vector() : xAxis(0), yAxis(0), startingX(0), startingY(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Vector::Vector(double xAxis, double yAxis, double zAxis) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis), startingX(0), startingY(0), startingZ(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Vector::Vector(double xAxis, double yAxis, double zAxis, double xOrigin, double yOrigin, double zOrigin) : xAxis(xAxis), yAxis(yAxis), startingX(xOrigin), startingY(yOrigin), startingZ(zOrigin)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Vector::~Vector()
{
}

Vector Vector::operator+(const Vector & rhs)
{
	return Vector(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis, startingX, startingY, startingZ);
}

Vector& Vector::operator+=(const Vector & rhs)
{
	this->xAxis += rhs.xAxis;
	this->yAxis += rhs.yAxis;
	this->zAxis += rhs.zAxis;
	return *this;
}

Vector Vector::operator-(const Vector & rhs)
{
	return Vector(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis, startingX, startingY, startingZ);
}

Vector& Vector::operator-=(const Vector & rhs)
{
	this->xAxis -= rhs.xAxis;
	this->yAxis -= rhs.yAxis;
	return *this;
}

Vector Vector::operator*(const double & rhs)
{
	return Vector(xAxis * rhs, yAxis * rhs, zAxis * rhs, startingX, startingY, startingZ);
}

Vector Vector::operator*(const Vector & rhs)
{
	return Vector(xAxis * rhs.xAxis, yAxis * rhs.yAxis, zAxis * rhs.zAxis, startingX, startingY, startingZ);
}

Vector Vector::operator/(const double & rhs)
{
	return Vector(xAxis / rhs, yAxis / rhs, zAxis / rhs, startingX, startingY, startingZ);
}

Vector Vector::operator/(const Vector & rhs)
{
	return Vector(xAxis / rhs.xAxis, yAxis / rhs.yAxis, zAxis / rhs.zAxis, startingX, startingY, startingZ);
}

Point Vector::ToPoint()
{
	return Point(xAxis, yAxis, zAxis);
}

void Vector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	offsetX += (startingX * Linal::FIELDWIDTH);
	offsetY -= (startingY * Linal::FIELDHEIGHT);
	application->DrawLine(offsetX, offsetY, offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT));
}

Color Vector::GetColor()
{
	return myColor;
}

Vector operator*(const double & lhs, const Vector & rhs)
{
	return Vector(lhs * rhs.xAxis, lhs * rhs.yAxis, lhs * rhs.xAxis);
}
