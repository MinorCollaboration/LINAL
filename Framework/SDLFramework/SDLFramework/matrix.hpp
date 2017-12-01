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

		Vector operator*(const Vector& rhs);

		Matrix<T> operator*(const Matrix<T>& rhs);
		Matrix<Point> operator*(const Matrix<Point>& rhs);
		Matrix<Vector> operator*(const Matrix<Vector>& rhs);

		Vector ToVector();

		int GetWidth();
		int GetHeight();
	private:
		std::vector<T> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const;
	};

	template <class T>
	Vector operator*(const Matrix<T> lhs, const Vector& rhs);

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
		auto index = ConvertToIndex(x, y);
		if (index > Width - 1 * Height - 1)
			return 1;
		return matrix.at(index);
	}

	template <typename T>
	T Matrix<T>::Get(int x, int y)
	{
		auto index = ConvertToIndex(x, y);
		if (index > Width - 1 * Height - 1)
			return 1;
		return matrix.at(index);
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

	template<class T>
	inline Matrix<Point> Matrix<T>::operator*(const Matrix<Point>& rhs)
	{
		Matrix<Point> output = Matrix<Point>(rhs.GetWidth(), Height);

		for (int x = 1; x <= output.GetHeight(); x++) {
			for (int y = 1; y <= output.GetWidth(); y++) {
				Vector val = *this * rhs.Get(x, y).ToVector();
				/*for (int colrows = 1; colrows <= Width; colrows++) {
					auto LeftVal = ToVector();
					auto RightVal = rhs.Get(colrows, y).ToVector();
					auto test = *this * RightVal;
					val += LeftVal * RightVal;
				}*/

				output.Set(x, y, val.ToPoint());
			}
		}

		return output;
	}

	template<class T>
	inline Vector Matrix<T>::ToVector()
	{
		return Vector(Get(1, 1), Get(2,2));
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
				application->DrawText(str, posX + 10, posY -7);
			}
		}
	}

	template<class T>
	inline Vector Matrix<T>::operator*(const Vector & rhs)
	{
		double xAxis = Get(1, 1) * rhs.xAxis;
		double yAxis = Get(2, 2) * rhs.yAxis;

		return Vector(xAxis, yAxis);
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
			auto index = ConvertToIndex(x, y);
			if (index > Width - 1 * Height - 1)
				return Vector(0, 0);
			return matrix.at(index);
		}
		Vector Get(int x, int y) const {
			auto index = ConvertToIndex(x, y);
			if (index > Width - 1 * Height - 1)
				return Vector(0, 0);
			return matrix.at(index);
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

					val.Draw(application, offsetX, offsetY);

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
			auto index = ConvertToIndex(x, y);
			if (index > Width - 1 * Height - 1)
				return Point(0, 0);
			return matrix.at(index);
		}
		Point Get(int x, int y) const {
			auto index = ConvertToIndex(x, y);
			if (index > Width - 1 * Height - 1)
				return Point(0, 0);
			return matrix.at(index);
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

					// TESTCASE: CAN WE CONNECT THE DOTS //
					/*if (x > 1) {
						auto ap = matrix.at(ConvertToIndex(x - 1, y));
						Vector vec = Linal::Vector(val.xAxis - ap.xAxis, ap.yAxis - val.yAxis, val.xAxis, val.yAxis);
						vec.Draw(application, offsetX, offsetY);
					}
					if (y > 1) {
						auto ap = matrix.at(ConvertToIndex(x, y - 1));
						Vector vec = Linal::Vector(ap.xAxis - val.xAxis, ap.yAxis - val.yAxis, val.xAxis, val.yAxis);
						vec.Draw(application, offsetX, offsetY);
					}*/
					// END OF TESTCASE: CAN WE CONNECT THE DOTS //

					val.Draw(application, offsetX, offsetY);
				}
			}
		}

		int GetWidth() {
			return Width;
		}
		int GetWidth() const {
			return Width;
		}
		int GetHeight() {
			return Height;
		}
		int GetHeight() const {
			return Height;
		}
	private:
		std::vector<Point> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const {
			return (x - 1)*Width + (y - 1);
		}
	};

	static Linal::Matrix<float> GetTranslateMatrix(double t, double s)
	{
		auto matrix = Linal::Matrix<float>(3, 3);

		matrix.Set(1, 1, 1).Set(1, 2, 0).Set(1, 3, t);
		matrix.Set(2, 1, 0).Set(2, 2, 1).Set(2, 3, s);
		matrix.Set(3, 1, 0).Set(3, 2, 0).Set(3, 3, 1);

		return matrix;
	}

	static Linal::Matrix<float> GetScaleMatrix(double xScale, double yScale)
	{
		auto matrix = Linal::Matrix<float>(2, 2);

		matrix.Set(1, 1, xScale).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, yScale);

		return matrix;
	}

	static Linal::Matrix<int> GetZeroMatrix()
	{
		auto matrix = Linal::Matrix<int>(0, 0);

		matrix.Set(1, 1, 0).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, 0);

		return matrix;
	}

	static Linal::Matrix<int> GetIdentityMatrix()
	{
		auto matrix = Linal::Matrix<int>(2, 2);

		matrix.Set(1, 1, 1).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, 1);

		return matrix;
	}

	template<class T>
	Vector operator*(const Matrix<T> lhs, const Vector & rhs)
	{
		return Vector(lhs.Get(1, 1) * rhs.xAxis, lhs.Get(2, 2) * rhs.yAxis);
	}
}

#endif