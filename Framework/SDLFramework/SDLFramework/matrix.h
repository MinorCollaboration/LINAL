#ifndef SDLFRAMEWORK_MYMATRIX
#define SDLFRAMEWORK_MYMATRIX

#include <vector>

#include "FWApplication.h"

class Matrix
{
public:
	Matrix();
	~Matrix();

	void Matrix::Draw(FWApplication *& application, int offsetX, int offsetY);

	double Get(int x, int y);
	Matrix& Set(int x, int y, double v);

	int GetWidth();
	int GetHeight();
private:
	std::vector<std::vector<double>> matrix;
};

#endif