#include "vector.h"

using namespace Linal;

Vector::Vector()
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);

	startingX = rand() * (Canvas::WIDTH / Canvas::FIELDWIDTH);
	startingY = rand() * (Canvas::HEIGHT / Canvas::FIELDHEIGHT);
}

Vector::Vector(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);

	auto random = rand();

	startingX = rand() % (Canvas::WIDTH / Canvas::FIELDWIDTH);
	startingY = rand() % (Canvas::HEIGHT / Canvas::FIELDHEIGHT);
}

Vector::Vector(double xAxis, double yAxis, int xOrigin, int yOrigin) : xAxis(xAxis), yAxis(yAxis), startingX(xOrigin), startingY(yOrigin)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

Vector::~Vector()
{
}

Vector& Vector::operator+(const Vector & rhs)
{
	return Vector(xAxis + rhs.xAxis, yAxis + rhs.yAxis, startingX, startingY);
}

Vector& Vector::operator-(const Vector & rhs)
{
	return Vector(xAxis - rhs.xAxis, yAxis - rhs.yAxis, startingX, startingY);
}

Vector& Vector::operator*(const int & rhs)
{
	return Vector(xAxis * rhs, yAxis * rhs, startingX, startingY);
}

Vector& Vector::operator/(const int & rhs)
{
	auto toReturn = Vector(xAxis / rhs, yAxis / rhs, startingX, startingY);
	return toReturn;
}

void Vector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawLine(offsetX, offsetY, offsetX + (xAxis * Canvas::FIELDWIDTH), offsetY - (yAxis * Canvas::FIELDHEIGHT));
}

Color Vector::GetColor()
{
	return myColor;
}
