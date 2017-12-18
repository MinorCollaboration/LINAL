#ifndef SDLFRAMEWORK_LINAL_GRAPHICAL2D_CANVAS
#define SDLFRAMEWORK_LINAL_GRAPHICAL2D_CANVAS

#include "../../FWApplication.h"
#include "./../graphical3D/point.h"
#include "./point.h"
#include "./vector.h"

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

			std::vector<Linal::G2D::Vector> vectors;
			std::vector<Linal::G2D::Point> points;
		private:
		};
	}
}

#endif