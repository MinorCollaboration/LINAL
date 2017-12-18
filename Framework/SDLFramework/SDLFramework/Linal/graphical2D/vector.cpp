#include "./vector.h"
#include "../constants.h"

Linal::G2D::Vector::Vector() : xAxis(0), yAxis(0), startingX(0), startingY(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G2D::Vector::Vector(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis), startingX(0), startingY(0)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G2D::Vector::Vector(double xAxis, double yAxis, double xOrigin, double yOrigin) : xAxis(xAxis), yAxis(yAxis), startingX(xOrigin), startingY(yOrigin)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Linal::G2D::Vector::~Vector()
{
}

Linal::G2D::Vector Linal::G2D::Vector::operator+(const Linal::G2D::Vector & rhs)
{
	return Linal::G2D::Vector(xAxis + rhs.xAxis, yAxis + rhs.yAxis, startingX, startingY);
}

Linal::G2D::Vector& Linal::G2D::Vector::operator+=(const Linal::G2D::Vector & rhs)
{
	this->xAxis += rhs.xAxis;
	this->yAxis += rhs.yAxis;
	return *this;
}

Linal::G2D::Vector Linal::G2D::Vector::operator-(const Linal::G2D::Vector & rhs)
{
	return Linal::G2D::Vector(xAxis - rhs.xAxis, yAxis - rhs.yAxis, startingX, startingY);
}

Linal::G2D::Vector& Linal::G2D::Vector::operator-=(const Linal::G2D::Vector & rhs)
{
	this->xAxis -= rhs.xAxis;
	this->yAxis -= rhs.yAxis;
	return *this;
}

Linal::G2D::Vector Linal::G2D::Vector::operator*(const double & rhs)
{
	return Linal::G2D::Vector(xAxis * rhs, yAxis * rhs, startingX, startingY);
}

Linal::G2D::Vector Linal::G2D::Vector::operator*(const Linal::G2D::Vector & rhs)
{
	return Linal::G2D::Vector(xAxis * rhs.xAxis, yAxis * rhs.yAxis, startingX, startingY);
}

Linal::G2D::Vector Linal::G2D::Vector::operator/(const double & rhs)
{
	return Linal::G2D::Vector(xAxis / rhs, yAxis / rhs, startingX, startingY);
}

Linal::G2D::Vector Linal::G2D::Vector::operator/(const Linal::G2D::Vector & rhs)
{
	return Linal::G2D::Vector(xAxis / rhs.xAxis, yAxis / rhs.yAxis, startingX, startingY);
}

Linal::G2D::Point Linal::G2D::Vector::ToPoint()
{
	return Linal::G2D::Point(xAxis, yAxis);
}

void Linal::G2D::Vector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	offsetX += (startingX * Linal::FIELDWIDTH);
	offsetY -= (startingY * Linal::FIELDHEIGHT);
	application->DrawLine(offsetX, offsetY, offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT));
}

Color Linal::G2D::Vector::GetColor()
{
	return myColor;
}

Linal::G2D::Vector operator*(const double & lhs, const Linal::G2D::Vector & rhs)
{
	return Linal::G2D::Vector(lhs * rhs.xAxis, lhs * rhs.yAxis);
}
