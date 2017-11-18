#ifndef SDLFRAMEWORK_MYVECTOR
#define SDLFRAMEWORK_MYVECTOR

#include "FWApplication.h"
#include "canvas.h"

struct Color;

namespace Linal
{
	class Vector
	{
	public:
		Vector();
		Vector(double xAxis, double yAxis);
		Vector(double xAxis, double yAxis, int xOrigin, int yOrigin);
		~Vector();

		Vector& operator+(const Vector&);
		Vector& operator-(const Vector&);

		Vector& operator*(const int&);
		Vector& operator/(const int&);

		double xAxis;
		double yAxis;

		double startingY;
		double startingX;

		void Draw(FWApplication*& application, int offsetX, int offsetY);
		Color GetColor();
	private:
		Color myColor;
	};
}


#endif