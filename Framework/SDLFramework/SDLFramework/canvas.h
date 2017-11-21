#ifndef SDLFRAMEWORK_MYCANVAS
#define SDLFRAMEWORK_MYCANVAS

#include "FWApplication.h"
#include "vector.h"
#include "matrix.hpp"

namespace Linal
{
	class Vector;

	class Canvas
	{
	public:
		Canvas();
		~Canvas();

		void Draw(FWApplication*& application);

		std::vector<Vector> vectors;
		std::vector<Linal::Matrix<int>> matrixes;
	
		static const int	OFFSETX = 100;
		static const int	OFFSETY = 50;
		static const int	WIDTH = 500;
		static const int	HEIGHT = 500;
		static const int	FIELDWIDTH = 25;
		static const int	FIELDHEIGHT = 25;
	private:
	};
}



#endif