#pragma once 

#ifndef SDLFRAMEWORK_MATRIX
#define SDLFRAMEWORK_MATRIX

#include <memory>
#include <iomanip>

using namespace std;

#include "FWApplication.h"
#include "constants.h"
#include "drawable.h"

namespace Linal
{
	class Vector;
	class Point;

	template <class T>
	class Matrix
	{
	public:
		Matrix<T>();
		Matrix<T>(int x, int y);
		~Matrix<T>();

		T Get(int x, int y);
		T Get(int x, int y) const;
		Matrix<T>& Set(int x, int y, T v);

		void Draw(FWApplication *& application, int offsetX, int offsetY);

		Matrix<T> operator*(const Matrix<T>& rhs);

		int GetWidth();
		int GetHeight();
	private:
		std::vector<T> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const;
	};

	template <class T>
	Matrix<T>::Matrix() : Width(1), Height(1)
	{
		matrix{ std::vector<T>(Width * Height) };
	}

	template <typename T>
	Matrix<T>::Matrix(int x, int y) : Width(x), Height(y)
	{
		matrix = std::vector<T>(Width * Height);
	}

	template <typename T>
	Matrix<T>::~Matrix()
	{
	}

	template <typename T>
	T Matrix<T>::Get(int x, int y) const
	{
		return matrix.at(ConvertToIndex(x, y));
	}

	template <typename T>
	T Matrix<T>::Get(int x, int y)
	{
		return matrix.at(ConvertToIndex(x, y));
	}

	template <typename T>
	Matrix<T>& Matrix<T>::Set(int x, int y, T v)
	{
		matrix.at(ConvertToIndex(x, y)) = v;
		return *this;
	}

	template<class T>
	inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
	{
		Matrix<T> output = Matrix<T>(rhs.Width, Height);

		for (int x = 1; x <= output.Height; x++) {
			for (int y = 1; y <= output.Width; y++) {
				T val = 0;
				for (int colrows = 1; colrows <= Width; colrows++)
					val += Get(x, colrows) * rhs.Get(colrows, y);

				output.Set(x, y, val);
			}
		}

		return output;
	}

	template <typename T>
	void Matrix<T>::Draw(FWApplication *& application, int offsetX, int offsetY)
	{
		application->SetFontSize(12);

		for (int x = 1; x <= Height; x++)
		{
			for (int y = 1; y <= Width; y++)
			{
				auto val = matrix.at(ConvertToIndex(x, y));
				application->SetColor(Color(255, 0, 0, 255));

				int posX = (y * Linal::FIELDHEIGHT) + offsetX;
				int posY = (x * Linal::FIELDWIDTH) + offsetY;

				std::string str = std::to_string(val);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				application->DrawText(str, posX, posY);

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

	template <typename T>
	int Matrix<T>::ConvertToIndex(int x, int y) const
	{
		return (x - 1)*Width + (y - 1);
	}

	// Vector matrix specialization
	template <>
	class Matrix <Vector> {
	public:
		Matrix() : Width(1), Height(1) {
			matrix = std::vector<Vector>(Width * Height);
		}
		Matrix(int x, int y) : Width(x), Height(y) {
			matrix = std::vector<Vector>(Width * Height);
		}

		Vector Get(int x, int y) {
			return matrix.at(ConvertToIndex(x, y));
		}
		Vector Get(int x, int y) const {
			return matrix.at(ConvertToIndex(x, y));
		}
		Matrix<Vector>& Set(int x, int y, Vector v) {
			matrix.at(ConvertToIndex(x, y)) = v;
			return *this;
		}

		void Draw(FWApplication *& application, int offsetX, int offsetY) {
			for (int x = 1; x <= Height; x++)
			{
				for (int y = 1; y <= Width; y++)
				{
					auto val = matrix.at(ConvertToIndex(x, y));

					int posX = (y * Linal::FIELDHEIGHT) + offsetX;
					int posY = (x * Linal::FIELDWIDTH) + offsetY;

					val.Draw(application, posX, posY);

				}
			}
		}

		Matrix<Vector> operator*(const Matrix<Vector>& rhs);

		int GetWidth() {
			return Width;
		}
		int GetHeight() {
			return Height;
		}
	private:
		std::vector<Vector> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const {
			return (x - 1)*Width + (y - 1);
		}
	};

	template <>
	class Matrix <Point> {
	public:
		Matrix() : Width(1), Height(1) {
			matrix = std::vector<Point>(Width * Height);
		}
		Matrix(int x, int y) : Width(x), Height(y) {
			matrix = std::vector<Point>(Width * Height);
		}

		Point Get(int x, int y) {
			return matrix.at(ConvertToIndex(x, y));
		}
		Point Get(int x, int y) const {
			return matrix.at(ConvertToIndex(x, y));
		}

		Matrix<Point>& Set(int x, int y, Point v)
		{
			matrix.at(ConvertToIndex(x, y)) = v;
			return *this;
		}

		void Draw(FWApplication *& application, int offsetX, int offsetY) {
			for (int x = 1; x <= Height; x++)
			{
				for (int y = 1; y <= Width; y++)
				{
					auto val = matrix.at(ConvertToIndex(x, y));

					val.Draw(application, 400, 400);

				}
			}
		}

	private:
		std::vector<Point> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const {
			return (x - 1)*Width + (y - 1);
		}
	};

	static Linal::Matrix<float> GetTranslateMatrix()
	{
		auto matrix = Linal::Matrix<float>(3, 3);

		matrix.Set(1, 1, 1).Set(1, 2, 0).Set(1, 3, 0.1);
		matrix.Set(2, 1, 0).Set(2, 2, 1).Set(2, 3, 0.1);
		matrix.Set(3, 1, 0).Set(3, 2, 0).Set(3, 3, 1);

		return matrix;
	}

	/*static Linal::Matrix<float>* GetScaleMatrix(int... scale)
	{

	}*/
}


#endif