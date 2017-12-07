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
	T Matrix<T>::Get(int x, int y)
	{
		return matrix.at(ConvertToIndex(x, y));
	}

	template <typename T>
	T Matrix<T>::Get(int x, int y) const
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
			for (int y = Width; y >= 1; y--) {
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
		Matrix<Point> output = Matrix<Point>(rhs.GetWidth());

		int width = output.GetWidth();
		int height = output.GetHeight();

		for (int x = 1; x <= output.GetHeight(); x++) {
			for (int y = 1; y <= output.GetWidth(); y++) {
				T val = 0;
				for (int colrows = 1; colrows <= Width; colrows++) {
					double leftVal = Get(x, colrows);
					double rightVal = rhs.matrix.at(ConvertToIndex(colrows, y));
					auto test = leftVal * rightVal;
					val += test;
				}

				output.Set(x, y, val);
				//Vector val = Vector(Get(x, y), rhs.Get(x, y));
				/*for (int colrows = 1; colrows <= Width; colrows++) {
					auto LeftVal = ToVector();
					auto RightVal = rhs.Get(colrows, y).ToVector();
					auto test = *this * RightVal;
					val += LeftVal * RightVal;
				}

				output.Set(x, y, val.ToPoint());*/
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

		application->SetColor(Color(255, 0, 0, 255));
		for (int y = Height; y >= 1; y--)
		{
			for (int x = 1; x <= Width; x++)
			{
				auto val = matrix.at(ConvertToIndex(x, y));

				int posX = (x * Linal::FIELDWIDTH) + offsetX;
				int posY = offsetY - (y * Linal::FIELDHEIGHT);

				std::string str = std::to_string(val);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				application->DrawText(str, posX + 10, posY - 7);
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
		return (x - 1)*Height + (y - 1);
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
		Matrix() : Width(1), Height(2) {
			matrix = std::vector<double>(Width * Height);
		}
		Matrix(int x) : Width(x), Height(2) { 
			matrix = std::vector<double>(Width * Height);
		}

		Point Get(int index) { 
			return Point(matrix.at(ConvertToIndex(index, 2)), matrix.at(ConvertToIndex(index, 1)));
		}
		Point Get(int index) const {
			return Point(matrix.at(ConvertToIndex(index, 2)), matrix.at(ConvertToIndex(index, 1)));
		}
		Matrix<Point>& Set(int index, Point p) { 
			int indexX = ConvertToIndex(index, 2);
			int indexY = ConvertToIndex(index, 1);

			matrix.at(indexX) = p.xAxis;
			matrix.at(indexY) = p.yAxis;

			return *this;
		}
		Matrix<Point>& Set(int x, int y, int val) {
			matrix.at(ConvertToIndex(x, y)) = val;

			return *this;
		}

		void Draw(FWApplication *& application, int offsetX, int offsetY) {
			for (int i = 1; i <= Width; i++)
			{
				auto point = Get(i);
				point.Draw(application, offsetX, offsetY);
			}
		}

		int GetWidth() { return Width; }
		int GetWidth() const { return Width; }
		int GetHeight() { return Height; }
		int GetHeight() const { return Height; }
		std::vector<double> matrix;
	private:
		int Width;
		int Height;

		int ConvertToIndex(int x, int y) const { 
			return (x - 1)*Height + (y - 1);
		}
	};

	static Linal::Matrix<float> GetTranslateMatrix(double t, double s)
	{
		auto matrix = Linal::Matrix<float>(3, 3);

		matrix.Set(1, 3, 1).Set(2, 3, 0).Set(3, 3, t);
		matrix.Set(1, 2, 0).Set(2, 2, 1).Set(3, 2, s);
		matrix.Set(1, 1, 0).Set(2, 1, 0).Set(3, 1, 1);

		return matrix;
	}

	static Linal::Matrix<float> GetScaleMatrix(double xScale, double yScale)
	{
		auto matrix = Linal::Matrix<float>(2, 2);

		matrix.Set(1, 2, xScale).Set(2, 2, 0);
		matrix.Set(1, 1, 0).Set(2, 1, yScale);

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