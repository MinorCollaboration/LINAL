#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::~Matrix()
{
}

double Matrix::Get(int x, int y)
{
	return matrix[x][y];
}

Matrix& Matrix::Set(int x, int y, double v)
{
	matrix[x][y] = v;
	return *this;
}

void Matrix::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			application->DrawText("A", 1, 2);
		}
	}
}

int Matrix::GetWidth()
{
	return matrix.size();
}

int Matrix::GetHeight()
{
	int maxHeight = 0;

	for (auto row : matrix)
	{
		if (row.size() > maxHeight)
			maxHeight = row.size();
	}

	return maxHeight;
}
