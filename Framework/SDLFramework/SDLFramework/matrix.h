#ifndef SDLFRAMEWORK_MATRIX
#define SDLFRAMEWORK_MATRIX

#include <vector>
#include <memory>

#include "FWApplication.h"

namespace Linal
{
	template <class T> class Matrix;
	template <typename T> Matrix<T>& operator*(Matrix<T>& out, const Matrix<T>& rhs);

	template <class T>
	class Matrix
	{
	public:
		Matrix<T>();
		Matrix<T>(int x, int y);
		~Matrix<T>();

		void Matrix::Draw(FWApplication *& application, int offsetX, int offsetY);

		T Get(int x, int y);
		T Get(int x, int y) const;
		Matrix<T>* Set(int x, int y, T v);

		Matrix<T>& operator*(const Matrix<T>& rhs);
		friend Matrix<T>& operator*(Matrix<T>& out, const Matrix<T>& rhs);

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
	T Matrix<T>::Get(int x, int y) const
	{
		int index = (x - 1)*Width + (y - 1);
		return matrix->at(index);
	}

	template <typename T>
	T Matrix<T>::Get(int x, int y)
	{
		int index = (x - 1)*Width + (y - 1);
		return matrix->at(index);
	}

	template <typename T>
	Matrix<T>* Matrix<T>::Set(int x, int y, T v)
	{
		int index = (x - 1)*Width + (y - 1);
		matrix->at(index) = v;
		return this;
	}

	template<class T>
	inline Matrix<T>& Matrix<T>::operator*(const Matrix<T>& rhs)
	{
		Matrix<T>* output = new Matrix<T>(rhs.Width, Height);

		for (int x = 1; x <= output->Height; x++)
		{
			for (int y = 1; y <= output->Width; y++)
			{
				auto test = Get(x, 1) * rhs.Get(1, y) + Get(x, 2) * rhs.Get(2, y);
				output->Set(x, y, test);
			}
		}

		return *output;
	}

	template <typename T>
	Matrix<T>& Linal::operator*(Matrix<T>& out, const Matrix<T>& rhs)
	{
		// TODO: insert return statement here
		return out;
	}

	template <typename T>
	void Matrix<T>::Draw(FWApplication *& application, int offsetX, int offsetY)
	{
		
		for (int x = 1; x <= Height; x++)
		{
			for (int y = 1; y <= Width; y++)
			{
				int index = (x - 1)*Width + (y - 1);
				auto val = matrix->at(index);
				application->SetColor(Color(255, 0, 0, 255));

				int posX = (y * Linal::Canvas::FIELDHEIGHT) + offsetX;
				int posY = (x * Linal::Canvas::FIELDWIDTH) + offsetY;

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