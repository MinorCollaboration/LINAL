#ifndef SDLFRAMEWORK_MYCANVAS
#define SDLFRAMEWORK_MYCANVAS

#include "FWApplication.h"
#include "myvector.h"
#include "matrix.h"

class MyVector;

class MyCanvas
{
public:
	MyCanvas();
	~MyCanvas();

	void Draw(FWApplication*& application);

	std::vector<MyVector> vectors;
	std::vector<Matrix> matrixs;
	
	static const int	OFFSETX = 100;
	static const int	OFFSETY = 50;
	static const int	WIDTH = 500;
	static const int	HEIGHT = 500;
	static const int	FIELDWIDTH = 25;
	static const int	FIELDHEIGHT = 25;
private:
};

#endif