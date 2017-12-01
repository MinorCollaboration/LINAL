#ifndef SDLFRAMEWORK_VECTOR
#define SDLFRAMEWORK_VECTOR

#include "FWApplication.h"
#include "point.h"

struct Color;

namespace Linal
{
	class Canvas;
	class Point;

	class Vector
	{
	public:
		Vector();
		Vector(double xAxis, double yAxis);
		Vector(double xAxis, double yAxis, int xOrigin, int yOrigin);
		~Vector();

		Vector operator+(const Vector&);
		Vector& operator+=(const Vector&);
		Vector operator-(const Vector&);
		Vector& operator-=(const Vector&);

		Vector operator*(const double&);
		Vector operator/(const double&);

		double xAxis;
		double yAxis;

		double startingY;
		double startingX;

		Point ToPoint();

		void Draw(FWApplication*& application, int offsetX, int offsetY);
		Color GetColor();
	private:
		Color myColor;
	};

}

Linal::Vector operator*(const double&, const Linal::Vector&);

#endif