#ifndef SDLFRAMEWORK_LINAL_GRAPHICAL3D_POINT
#define SDLFRAMEWORK_LINAL_GRAPHICAL3D_POINT

#include "../../FWApplication.h"

#include "vector.h"

struct Color;

namespace Linal
{
	namespace G3D
	{
		class Vector;

		class Point
		{
		public:
			Point();
			Point(double xAxis, double yAxis, double zAxis);
			~Point();

			double xAxis;
			double yAxis;
			double zAxis;

			Vector ToVector();

			void Draw(FWApplication*& application, int offsetX, int offsetY);
		};
	}
}

#endif