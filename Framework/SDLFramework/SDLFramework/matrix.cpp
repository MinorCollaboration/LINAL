#include "matrix.h"

using namespace Linal;

template <class T>
Matrix<T>::Matrix() : Width(1), Height(1)
{
	matrix = new std::vector<std::vector<T>>();
}

template <class T>
Matrix<T>::Matrix(int x, int y) : Width(x), Height(1)
{

}

template <class T>
Matrix<T>::~Matrix()
{
}

template <class T>
double Matrix<T>::Get(int x, int y)
{
	return matrix[x][y];
}

template <class T>
Matrix<T>& Matrix<T>::Set(int x, int y, T v)
{
	matrix[x][y] = v;
	return *this;
}

template <class T>
void Matrix<T>::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			application->DrawText("A", 1, 2);
		}
	}
}

template <class T>
int Matrix<T>::GetWidth()
{
	return Width;
}

template <class T>
int Matrix<T>::GetHeight()
{
	return Height;
}