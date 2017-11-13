#include "myvector.h"

MyVector::MyVector()
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);

	startingX = rand() * (MyCanvas::WIDTH / MyCanvas::FIELDWIDTH);
	startingY = rand() * (MyCanvas::HEIGHT / MyCanvas::FIELDHEIGHT);
}

MyVector::MyVector(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);

	auto random = rand();

	startingX = rand() % (MyCanvas::WIDTH / MyCanvas::FIELDWIDTH);
	startingY = rand() % (MyCanvas::HEIGHT / MyCanvas::FIELDHEIGHT);
}

MyVector::MyVector(double xAxis, double yAxis, int xOrigin, int yOrigin) : xAxis(xAxis), yAxis(yAxis), startingX(xOrigin), startingY(yOrigin)
{
	myColor = Color(rand() * 255, rand() * 255, rand() * 255, 255);
}

MyVector::~MyVector()
{
}

MyVector& MyVector::operator+(const MyVector & rhs)
{
	return MyVector(xAxis + rhs.xAxis, yAxis + rhs.yAxis, startingX, startingY);
}

MyVector& MyVector::operator-(const MyVector & rhs)
{
	return MyVector(xAxis - rhs.xAxis, yAxis - rhs.yAxis, startingX, startingY);
}

MyVector& MyVector::operator*(const int & rhs)
{
	return MyVector(xAxis * rhs, yAxis * rhs, startingX, startingY);
}

MyVector& MyVector::operator/(const int & rhs)
{
	auto toReturn = MyVector(xAxis / rhs, yAxis / rhs, startingX, startingY);
	return toReturn;
}

void MyVector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawLine(offsetX, offsetY, offsetX + (xAxis * MyCanvas::FIELDWIDTH), offsetY - (yAxis * MyCanvas::FIELDHEIGHT));
}

Color MyVector::GetColor()
{
	return myColor;
}
