#ifndef SDLFRAMEWORK_VECTOR
#define SDLFRAMEWORK_VECTOR

#include "../../FWApplication.h"
#include "point.h"

struct Color;

namespace Linal
{
	namespace G2D
	{
		class Canvas;
		class Point;

		class Vector
		{
		public:
			Vector();
			Vector(double xAxis, double yAxis);
			Vector(double xAxis, double yAxis, double xOrigin, double yOrigin);
			~Vector();

			Vector operator+(const Vector&);
			Vector& operator+=(const Vector&);
			Vector operator-(const Vector&);
			Vector& operator-=(const Vector&);

			Vector operator*(const double&);
			Vector operator*(const Vector&);
			Vector operator/(const double&);
			Vector operator/(const Vector&);

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
	

}

Linal::G2D::Vector operator*(const double&, const Linal::G2D::Vector&);

#endif