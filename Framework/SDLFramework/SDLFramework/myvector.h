#ifndef SDLFRAMEWORK_MYVECTOR
#define SDLFRAMEWORK_MYVECTOR

#include "FWApplication.h"
#include "mycanvas.h"

class MyVector
{
public:
	MyVector();
	~MyVector();

	signed int xAxis;
	signed int yAxis;

	void Draw(FWApplication*& application, int offsetX, int offsetY);
private:

};
#endif