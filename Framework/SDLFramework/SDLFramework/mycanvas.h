#ifndef SDLFRAMEWORK_MYCANVAS
#define SDLFRAMEWORK_MYCANVAS

#include "FWApplication.h"

class MyCanvas
{
public:
	MyCanvas();
	~MyCanvas();

	void Draw(FWApplication*& application);
private:
	const int	OFFSETX = 100;
	const int	OFFSETY = 50;
	const int	WIDTH = 500;
	const int	HEIGHT = 500;
	const int	FIELDWIDTH = 50;
	const int	FIELDHEIGHT = 50;
};

#endif