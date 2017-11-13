#ifndef SDLFRAMEWORK_MYCANVAS
#define SDLFRAMEWORK_MYCANVAS

#include "FWApplication.h"
#include "myvector.h"

class MyVector;

class MyCanvas
{
public:
	MyCanvas();
	~MyCanvas();

	void Draw(FWApplication*& application);

	std::vector<MyVector> vectors;
	
	const int	OFFSETX = 100;
	const int	OFFSETY = 50;
	const int	WIDTH = 500;
	const int	HEIGHT = 500;
	static const int	FIELDWIDTH = 50;
	static const int	FIELDHEIGHT = 50;
private:
};

#endif