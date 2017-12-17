#ifndef SDLFRAMEWORK_LINAL_GRAPHICAL2D_POINT
#define SDLFRAMEWORK_LINAL_GRAPHICAL2D_POINT

#include "../../FWApplication.h"

#include "vector.h"

struct Color;

namespace Linal
{
	namespace G2D
	{
		class Vector;

		class Point
		{
		public:
			Point();
			Point(double xAxis, double yAxis);
			~Point();

			double xAxis;
			double yAxis;

			Vector ToVector();

			void Draw(FWApplication*& application, int offsetX, int offsetY);
		};
	}
	
}

Linal::G2D::Vector operator*(const int&, const Linal::G2D::Point&);

#endif