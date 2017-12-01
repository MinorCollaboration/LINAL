#ifndef SDLFRAMEWORK_POINT
#define SDLFRAMEWORK_POINT

#include "FWApplication.h"

#include "vector.h"

struct Color;

namespace Linal
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

		static const int	SIZE = 7;
	};
}

Linal::Vector operator*(const int&, const Linal::Point&);

#endif