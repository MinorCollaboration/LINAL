#pragma once 

#ifndef SDLFRAMEWORK_MATRIX
#define SDLFRAMEWORK_MATRIX

#include <memory>
#include <iomanip>
#include <math.h>
#include <typeinfo>

using namespace std;

#include "FWApplication.h"
#include "Linal/constants.h"
#include "drawable.h"

namespace Linal
{
	namespace G2D
	{
		class Vector;
		class Point;
	}
	

	template <class T>
	class Matrix
	{
	public:
		Matrix<T>();
		Matrix<T>(int col, int row);
		~Matrix<T>();

		T Get(int col, int row);
		T Get(int col, int row) const;
		Matrix<T>& Set(int col, int row, T v);

		void Draw(FWApplication *& application, int offsetX, int offsetY);

		G2D::Vector operator*(const G2D::Vector& rhs);

		Matrix<T> operator*(const Matrix<T>& rhs);
		Matrix<G2D::Point> operator*(const Matrix<G2D::Point>& rhs);

		G2D::Vector ToVector();

		Matrix<T>& AddHelpLine();

		static Matrix<T> AddHelpLine(const Linal::Matrix<T>& toCopy);

		Matrix<T>& RemoveHelpLine();

		static Matrix<T>& RemoveHelpLine(const Linal::Matrix<T>& toCopy);

		int GetWidth();
		int GetWidth() const;
		int GetHeight();
		int GetHeight() const;
	private:
		std::vector<T> matrix;
		int Width;
		int Height;

		int ConvertToIndex(int col, int row) const;
	};

	template <class T>
	Matrix<T>& Matrix<T>::AddHelpLine() {
		auto replacement = std::vector<double>(Width * (Height + 1));

		for (int row = 1; row <= GetHeight(); row++)
			for (int col = 1; col <= GetWidth(); col++)
				replacement.at(ConvertToIndex(row, col)) = matrix.at(ConvertToIndex(row, col));

		for (int col = 1; col <= GetWidth(); col++)
			replacement.at(ConvertToIndex(GetHeight() + 1, col)) = 1;

		matrix = replacement;
		return *this;
	}

	template <class T>
	Matrix<T> Matrix<T>::AddHelpLine(const Linal::Matrix<T>& toCopy) {
		auto copiedMatrix = Matrix<T>(toCopy.GetHeight() + 1, toCopy.GetWidth());
		auto replacement = std::vector<double>(toCopy.Width * (toCopy.Height + 1));

		for (int row = 1; row <= toCopy.GetHeight(); row++)
			for (int col = 1; col <= toCopy.GetWidth(); col++)
				replacement.at(toCopy.ConvertToIndex(row, col)) = toCopy.matrix.at(toCopy.ConvertToIndex(row, col));

		for (int col = 1; col <= toCopy.GetWidth(); col++)
			replacement.at(toCopy.ConvertToIndex(toCopy.GetHeight() + 1, col)) = 1;

		copiedMatrix.matrix = replacement;
		return copiedMatrix;
	}

	template <class T>
	Matrix<T>& Matrix<T>::RemoveHelpLine() {
		auto replacement = std::vector<double>(Width, Height - 1);

		for (int row = 1; row <= GetHeight() - 1; row++)
			for (int col = 1; col <= GetWidth(); col++)
				replacement.at(ConvertToIndex(row, col)) = matrix.at(ConvertToIndex(row, col));

		matrix = replacement;
		return *this;
	}

	template <class T>
	Matrix<T>& Matrix<T>::RemoveHelpLine(const Linal::Matrix<T>& toCopy) {
		auto copiedMatrix = Matrix<T>(toCopy.Width, toCopy.Height -1);
		auto replacement = std::vector<double>(toCopy.Width * (toCopy.Height - 1));

		for (int row = 1; row <= toCopy.GetHeight() - 1; row++)
			for (int col = 1; col <= toCopy.GetWidth(); col++)
				replacement.at(toCopy.ConvertToIndex(row, col)) = toCopy.matrix.at(toCopy.ConvertToIndex(row, col));

		copiedMatrix.matrix = replacement;
		return copiedMatrix;
	}

	template <class T>
	G2D::Vector operator*(const Matrix<T> lhs, const G2D::Vector& rhs);

	template <class T>
	Matrix<T>::Matrix() : Width(1), Height(1)
	{
		matrix{ std::vector<T>(Width * Height) };
	}

	template <typename T>
	Matrix<T>::Matrix(int row, int col) : Width(col), Height(row)
	{
		matrix = std::vector<T>(Width * Height);
	}

	template <typename T>
	Matrix<T>::~Matrix()
	{
	}

	template <typename T>
	T Matrix<T>::Get(int row, int col)
	{
		return matrix.at(ConvertToIndex(row, col));
	}

	template <typename T>
	T Matrix<T>::Get(int row, int col) const
	{
		return matrix.at(ConvertToIndex(row, col));
	}

	template <typename T>
	Matrix<T>& Matrix<T>::Set(int row, int col, T v)
	{
		matrix.at(ConvertToIndex(row, col)) = v;
		return *this;
	}

	template <class T>
	static Matrix<T> AddHelpLine(const Matrix<T>& input)
	{
		Matrix<T> output = Matrix<T>{ input.GetHeight() + 1, input.GetWidth() };

		for (int row = 1; row <= input.GetHeight(); row++)
			for (int col = 1; col <= input.GetWidth(); col++)
				output.Set(row, col, input.Get(row, col));

		for (int col = 1; col <= input.GetWidth(); col++)
			output.Set(input.GetHeight() + 1, col, 1);

		return output;
	}

	template <class T>
	static Matrix<T> RemoveHelpLine(const Matrix<T>& input)
	{
		Matrix<T> output = Matrix<T>{ input.GetHeight() - 1, input.GetWidth() };

		for (int row = 1; row <= output.GetHeight(); row++)
			for (int col = 1; col <= input.GetWidth(); col++)
				output.Set(row, col, input.Get(row, col));

		return output;
	}

	template<class T>
	inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& initialRhs)
	{
		auto lhs = *this;
		auto rhs = initialRhs;

		int lhsHelpLines = 0;
		int rhsHelpLines = 0;

		Matrix<T> output = Matrix<T>(rhs.GetHeight(), lhs.GetWidth());

		if (lhs.GetWidth() < rhs.GetHeight())
		{
			AddHelpLine(lhs);
			lhsHelpLines++;
		}
		else if (lhs.GetWidth() > rhs.GetHeight())
		{
			output = AddHelpLine(output);
			rhs = AddHelpLine(rhs);
			rhsHelpLines++;
		}

		for (int row = 1; row <= output.GetHeight(); row++)
		{
			for (int col = 1; col <= output.GetWidth(); col++)
			{
				T val = 0;
				for (int colrows = 1; colrows <= Width; colrows++)
					val += Get(row, colrows) * rhs.Get(colrows, col);

				output.Set(row, col, val);
			}
		}

		if (lhsHelpLines) {
			for (int i = 0; i < lhsHelpLines; i++)
				lhs = RemoveHelpLine(lhs);
		}
		else if (rhsHelpLines) {
			for (int i = 0; i < rhsHelpLines; i++) {
				output = output.RemoveHelpLine();
				rhs = rhs.RemoveHelpLine();
			}
		}

		return output;
	}

	template<class T>
	inline Matrix<G2D::Point> Matrix<T>::operator*(const Matrix<G2D::Point>& initialRhs)
	{
		auto lhs = *this;
		auto rhs = initialRhs;

		int lhsHelpLines = 0;
		int rhsHelpLines = 0;

		Matrix<G2D::Point> output = Matrix<G2D::Point>(rhs.GetWidth());

		if (lhs.GetWidth() < rhs.GetHeight())
		{
			AddHelpLine(lhs);
			lhsHelpLines++;
		}
		else if (lhs.GetWidth() > rhs.GetHeight())
		{
			output = output.AddHelpLine();
			rhs = rhs.AddHelpLine();
			rhsHelpLines++;
		}

		for (int row = 1; row <= output.GetHeight(); row++)
		{
			for (int col = 1; col <= output.GetWidth(); col++)
			{
				T val = 0;
				for (int colrows = 1; colrows <= Width; colrows++)
					val += lhs.Get(row, colrows) * rhs.matrix.at(rhs.ConvertToIndex(colrows, col));

				output.Set(row, col, val);
			}
		}

		if (lhsHelpLines) {
			for (int i = 0; i < lhsHelpLines; i++)
				lhs = RemoveHelpLine(lhs);
		}
		else if (rhsHelpLines) {
			for (int i = 0; i < rhsHelpLines; i++) {
				output = output.RemoveHelpLine();
				rhs = rhs.RemoveHelpLine();
			}
		}

		return output;
	}

	/* */
	template<class T>
	inline G2D::Vector Matrix<T>::ToVector()
	{
		return G2D::Vector(Get(1, 1), Get(2,2));
	}
	/* */

	template <typename T>
	void Matrix<T>::Draw(FWApplication *& application, int offsetX, int offsetY)
	{
		application->SetFontSize(12);

		application->SetColor(Color(255, 0, 0, 255));
		for (int row = 1; row <= Height; row++)
		{
			for (int col = 1; col <= Width; col++)
			{
				auto val = matrix.at(ConvertToIndex(row, col));

				int posX = (col * Linal::FIELDWIDTH) + offsetX;
				int posY = (row * Linal::FIELDHEIGHT) + offsetY;

				std::string str = std::to_string(val);
				str.erase(str.find_last_not_of('0') + 1, std::string::npos);
				application->DrawText(str, posX + 10, posY - 7);
			}
		}
	}

	template<class T>
	inline G2D::Vector Matrix<T>::operator*(const G2D::Vector & rhs)
	{
		double xAxis = Get(1, 1) * rhs.xAxis;
		double yAxis = Get(2, 2) * rhs.yAxis;

		return G2D::Vector(xAxis, yAxis);
	}

	template <typename T>
	int Matrix<T>::GetWidth()
	{
		return Width;
	}

	template <typename T>
	int Matrix<T>::GetWidth() const
	{
		return Width;
	}

	template <typename T>
	int Matrix<T>::GetHeight()
	{
		return Height;
	}

	template <typename T>
	int Matrix<T>::GetHeight() const
	{
		return Height;
	}

	template <typename T>
	int Matrix<T>::ConvertToIndex(int row, int col) const
	{
		return (row - 1)*Width + (col - 1);
	}

	template <>
	class Matrix <G2D::Point> {
	public:
		Matrix() : Width(1), Height(2) {
			matrix = std::vector<double>(Width * Height);
		}
		Matrix(int cols) : Width(cols), Height(2) { 
			matrix = std::vector<double>(Width * Height);
		}

		G2D::Point Get(int index) { 
			return G2D::Point(matrix.at(ConvertToIndex(2, index)), matrix.at(ConvertToIndex(1, index)));
		}
		G2D::Point Get(int index) const {
			return G2D::Point(matrix.at(ConvertToIndex(2, index)), matrix.at(ConvertToIndex(1, index)));
		}
		Matrix<G2D::Point>& Set(int index, G2D::Point p) {
			int indexX = ConvertToIndex(2, index);
			int indexY = ConvertToIndex(1, index);

			matrix.at(indexX) = p.xAxis;
			matrix.at(indexY) = p.yAxis;

			return *this;
		}
		Matrix<G2D::Point>& Set(int row, int col, double val) {
			matrix.at(ConvertToIndex(row, col)) = val;

			return *this;
		}
		void Draw(FWApplication *& application, int offsetX, int offsetY) {
			for (int index = 1; index <= Width; index++)
			{
				auto point = Get(index);
				point.Draw(application, offsetX, offsetY);
			}

			for (int leftIndex = 1; leftIndex <= Width; leftIndex++)
			{
				int rightIndex = (leftIndex == Width) ? 1 : leftIndex + 1;
				auto leftPoint = Get(leftIndex);
				auto rightPoint = Get(rightIndex);

				G2D::Vector v = G2D::Vector(rightPoint.xAxis - leftPoint.xAxis, rightPoint.yAxis - leftPoint.yAxis, leftPoint.xAxis, leftPoint.yAxis);
				v.Draw(application, offsetX, offsetY);
			}
		}
		Matrix<G2D::Point> AddHelpLine() {
			Matrix<G2D::Point> output = Matrix<G2D::Point>{ GetWidth() };
			output.matrix = std::vector<double>(GetWidth() * (GetHeight() + 1));
			output.Height++;

			for (int col = 1; col <= GetWidth(); col++) {
				output.Set(col, Get(col));
				output.matrix.at(ConvertToIndex(GetHeight() + 1, col)) = 1;
			}

			return output;
		}


		Matrix<G2D::Point> RemoveHelpLine() {
			Matrix<G2D::Point> output = Matrix<G2D::Point>{ GetWidth() };
			output.matrix = std::vector<double>(GetWidth() * 2);
			output.Height = 2;

			for (int col = 1; col <= GetWidth(); col++)
				output.Set(col, Get(col));

			return output;
		}

		int GetWidth() { return Width; }
		int GetWidth() const { return Width; }
		int GetHeight() { return Height; }
		int GetHeight() const { return Height; }

	// protected: 
		std::vector<double> matrix;

		int ConvertToIndex(int x, int y) const { 
			return (x - 1)*Width + (y - 1);
		}
		
	private:
		int Width;
		int Height;

	};

	static Linal::Matrix<double> GetTranslateMatrix(double t, double s)
	{
		auto matrix = Linal::Matrix<double>(3, 3);

		matrix.Set(1, 1, 1).Set(1, 2, 0).Set(1, 3, t);
		matrix.Set(2, 1, 0).Set(2, 2, 1).Set(2, 3, s);
		matrix.Set(3, 1, 0).Set(3, 2, 0).Set(3, 3, 1);

		return matrix;
	}

	static Linal::Matrix<double> GetScaleMatrix(double xScale, double yScale)
	{
		auto matrix = Linal::Matrix<double>(2, 2);

		matrix.Set(1, 1, xScale).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, yScale);

		return matrix;
	}

	static Linal::Matrix<double> GetZeroMatrix()
	{
		auto matrix = Linal::Matrix<double>(0, 0);

		matrix.Set(1, 1, 0).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, 0);

		return matrix;
	}

	static Linal::Matrix<double> GetIdentityMatrix()
	{
		auto matrix = Linal::Matrix<double>(2, 2);

		matrix.Set(1, 1, 1).Set(1, 2, 0);
		matrix.Set(2, 1, 0).Set(2, 2, 1);

		return matrix;
	}

	static Linal::Matrix<double> GetRotateMatrix(double degree)
	{
		double piRad = (degree * M_PI) / 180; //1 * degree;

		auto matrix = Linal::Matrix<double>(3, 3);
		
		matrix.Set(1, 1, cos(piRad)).Set(1, 2, -sin(piRad)).Set(1, 3, 0);
		matrix.Set(2, 1, sin(piRad)).Set(2, 2, cos(piRad)).Set(2, 3, 0);
		matrix.Set(3, 1, 0).Set(3, 2, 0).Set(3, 3, 1);

		return matrix;
	}
}

#endif