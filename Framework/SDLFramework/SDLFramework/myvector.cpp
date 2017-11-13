#include "myvector.h"

MyVector::MyVector()
{
}

MyVector::~MyVector()
{
}

void MyVector::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawLine(offsetX, offsetY, offsetX + (xAxis * MyCanvas::FIELDWIDTH), offsetY - (yAxis * MyCanvas::FIELDHEIGHT));
}
