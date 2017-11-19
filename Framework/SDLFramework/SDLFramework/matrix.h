#ifndef SDLFRAMEWORK_MATRIX
#define SDLFRAMEWORK_MATRIX

#include <vector>
#include <memory>

#include "FWApplication.h"

namespace Linal
{
	template <typename T>
	class Matrix
	{
	public:
		Matrix<T>();
		Matrix<T>(int x, int y);
		~Matrix<T>();

		void Matrix::Draw(FWApplication *& application, int offsetX, int offsetY);

		double Get(int x, int y);
		Matrix<T>* Set(int x, int y, T v);

		int GetWidth();
		int GetHeight();
	private:
		std::vector<T>* matrix;
		int Width;
		int Height;
	};

	template <typename T>
	Matrix<T>::Matrix() : Width(1), Height(1)
	{
		matrix { new std::vector<T>(Width * Height) };
	}

	template <typename T>
	Matrix<T>::Matrix(int x, int y) : Width(x), Height(y)
	{
		matrix = new std::vector<T>(Width * Height);
	}

	template <typename T>
	Matrix<T>::~Matrix()
	{
		delete matrix;
	}

	template <typename T>
	double Matrix<T>::Get(int x, int y)
	{
		return matrix[x*Width + y];
	}

	template <typename T>
	Matrix<T>* Matrix<T>::Set(int x, int y, T v)
	{
		//matrix->insert(x*Width + y, v);
		int index = (x - 1)*Width + y - 1;
		matrix->at(index) = v;
		return this;
	}

	template <typename T>
	void Matrix<T>::Draw(FWApplication *& application, int offsetX, int offsetY)
	{
		for (int y = 1; y <= Width; y++)
		{
			for (int x = 1; x <= Height; x++)
			{
				int index = (x - 1) * Width + y-1;
				auto val = matrix->at(index);
				application->SetColor(Color(255, 0, 0, 255));

				int posX = (x * Linal::Canvas::FIELDWIDTH) + offsetX;
				int posY = (y * Linal::Canvas::FIELDHEIGHT) + offsetY;

				application->SetFontSize(18);
				application->DrawText(std::to_string(val), posX, posY);
			}
		}
	}

	template <typename T>
	int Matrix<T>::GetWidth()
	{
		return Width;
	}

	template <typename T>
	int Matrix<T>::GetHeight()
	{
		return Height;
	}
}


#endif