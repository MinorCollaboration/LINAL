#ifndef SDLFRAMEWORK_MYVECTOR
#define SDLFRAMEWORK_MYVECTOR

#include "FWApplication.h"
#include "mycanvas.h"

struct Color;

class MyVector
{
public:
	MyVector();
	MyVector(double xAxis, double yAxis);
	MyVector(double xAxis, double yAxis, int xOrigin, int yOrigin);
	~MyVector();

	MyVector& operator+(const MyVector&);
	MyVector& operator-(const MyVector&);

	MyVector& operator*(const int&);
	MyVector& operator/(const int&);

	double xAxis;
	double yAxis;

	double startingY;
	double startingX;

	void Draw(FWApplication*& application, int offsetX, int offsetY);
	Color GetColor();
private:
	Color myColor;
};
#endif