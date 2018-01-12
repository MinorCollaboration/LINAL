#ifndef SDLFRAMEWORK_LINAL_GRAPHICAL3D_VECTOR
#define SDLFRAMEWORK_LINAL_GRAPHICAL3D_VECTOR

#include "../../FWApplication.h"

#include "3dpoint.h"

struct Color;

namespace Linal
{
	namespace G3D
	{
		class Canvas;
		class Point;

		class Vector
		{
		public:
			Vector();
			Vector(double xAxis, double yAxis, double zAxis);
			Vector(double xAxis, double yAxis, double zAxis, double xOrigin, double yOrigin, double zOrigin);
			~Vector();

			Vector operator+(const Vector&);
			Vector& operator+=(const Vector&);
			Vector operator-(const Vector&);
			Vector& operator-=(const Vector&);

			Vector operator*(const double&);
			Vector operator*(const Vector&);
			Vector operator/(const double&);
			Vector operator/(const Vector&);

			Vector GetUnitVector();

			double xAxis;
			double yAxis;
			double zAxis;

			double startingY;
			double startingX;
			double startingZ;

			Point ToPoint();

			void Draw(FWApplication*& application, double offsetX, double offsetY);
			Color GetColor();
		private:
			Color myColor;
		};

		Vector GetConnection(Point a, Point b);
	}
}

#endif