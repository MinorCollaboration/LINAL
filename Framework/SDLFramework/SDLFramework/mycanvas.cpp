#include "mycanvas.h"

MyCanvas::MyCanvas()
{
}

MyCanvas::~MyCanvas()
{
}

void MyCanvas::Draw(FWApplication*& application)
{
	auto defaultColor = Color(127, 127, 127, 255);

	application->SetColor(Color(0, 0, 0, 255));
	application->DrawLine(MyCanvas::OFFSETX, MyCanvas::OFFSETY, MyCanvas::OFFSETX, MyCanvas::HEIGHT + MyCanvas::OFFSETY, 5);
	application->DrawLine(MyCanvas::OFFSETX, MyCanvas::HEIGHT + MyCanvas::OFFSETY, MyCanvas::WIDTH + MyCanvas::OFFSETX, MyCanvas::HEIGHT + MyCanvas::OFFSETY, 5);

	// Draw the vertical lines
	application->SetColor(defaultColor);
	for (int x = MyCanvas::OFFSETX + MyCanvas::FIELDWIDTH; x <= MyCanvas::WIDTH + MyCanvas::OFFSETX; x += MyCanvas::FIELDWIDTH)
	{
		application->DrawLine(x, MyCanvas::HEIGHT + MyCanvas::OFFSETY, x, MyCanvas::OFFSETY, 2);
	}

	// Draw the horizontal lines
	application->SetColor(defaultColor);
	for (int y = MyCanvas::OFFSETY + MyCanvas::HEIGHT - MyCanvas::FIELDHEIGHT; y >= MyCanvas::OFFSETY; y -= MyCanvas::FIELDHEIGHT)
	{
		application->DrawLine(MyCanvas::WIDTH + MyCanvas::OFFSETX, y, MyCanvas::OFFSETX, y, 2);
	}

	for (auto vector : vectors)
	{
		application->SetColor(vector.GetColor());
		vector.Draw(application, MyCanvas::OFFSETX + (vector.startingX * MyCanvas::FIELDWIDTH), MyCanvas::OFFSETY + MyCanvas::HEIGHT - (vector.startingY * MyCanvas::FIELDHEIGHT));
	}
	application->SetColor(defaultColor);
}