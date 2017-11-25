#ifndef SDLFRAMEWORK_VECTOR
#define SDLFRAMEWORK_VECTOR

#include "FWApplication.h"

struct Color;

namespace Linal
{
	class Canvas;

	class Vector
	{
	public:
		Vector();
		Vector(double xAxis, double yAxis);
		Vector(double xAxis, double yAxis, int xOrigin, int yOrigin);
		~Vector();

		Vector operator+(const Vector&);
		Vector operator-(const Vector&);

		Vector operator*(const int&);
		Vector operator/(const int&);

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