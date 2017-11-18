#ifndef SDLFRAMEWORK_MYMATRIX
#define SDLFRAMEWORK_MYMATRIX

#include <vector>

#include "FWApplication.h"

namespace Linal
{
	template <class T>
	class Matrix
	{
	public:
		Matrix<T>();
		Matrix<T>(int x, int y);
		~Matrix();

		void Matrix::Draw(FWApplication *& application, int offsetX, int offsetY);

		double Get(int x, int y);
		Matrix& Set(int x, int y, T v);

		int GetWidth();
		int GetHeight();
	private:
		std::vector<std::vector<T>> matrix;
		int Width;
		int Height;
	};
}


#endif