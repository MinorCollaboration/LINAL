#ifndef SDLFRAMEWORK_POINT
#define SDLFRAMEWORK_POINT

#include "FWApplication.h"

struct Color;

namespace Linal
{
	class Point
	{
	public:
		Point(double xAxis, double yAxis);
		~Point();

		double xAxis;
		double yAxis;

		void Draw(FWApplication*& application, int offsetX, int offsetY);

		static const int	SIZE = 7;
	private:
	};
}

#endif