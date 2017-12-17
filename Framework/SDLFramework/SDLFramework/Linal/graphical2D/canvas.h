#ifndef SDLFRAMEWORK_CANVAS
#define SDLFRAMEWORK_CANVAS

#include "../../FWApplication.h"
#include "point.h"
#include "vector.h"

namespace Linal
{
	namespace G2D
	{
		class Vector;
		class Point;

		class Canvas
		{
		public:
			Canvas();
			~Canvas();

			void Draw(FWApplication*& application);

			std::vector<Vector> vectors;
			std::vector<Point> points;
		private:
		};
	}
}



#endif