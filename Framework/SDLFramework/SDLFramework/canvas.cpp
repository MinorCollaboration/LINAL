#include "canvas.h"

using namespace Linal;

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::Draw(FWApplication*& application)
{
	auto defaultColor = Color(127, 127, 127, 255);

	application->SetColor(Color(0, 0, 0, 255));
	application->DrawLine(Canvas::OFFSETX, Canvas::OFFSETY, Canvas::OFFSETX, Canvas::HEIGHT + Canvas::OFFSETY, 5);
	application->DrawLine(Canvas::OFFSETX, Canvas::HEIGHT + Canvas::OFFSETY, Canvas::WIDTH + Canvas::OFFSETX, Canvas::HEIGHT + Canvas::OFFSETY, 5);

	// Draw the vertical lines
	application->SetColor(defaultColor);
	for (int x = Canvas::OFFSETX + Canvas::FIELDWIDTH; x <= Canvas::WIDTH + Canvas::OFFSETX; x += Canvas::FIELDWIDTH)
	{
		application->DrawLine(x, Canvas::HEIGHT + Canvas::OFFSETY, x, Canvas::OFFSETY, 2);
	}

	// Draw the horizontal lines
	application->SetColor(defaultColor);
	for (int y = Canvas::OFFSETY + Canvas::HEIGHT - Canvas::FIELDHEIGHT; y >= Canvas::OFFSETY; y -= Canvas::FIELDHEIGHT)
	{
		application->DrawLine(Canvas::WIDTH + Canvas::OFFSETX, y, Canvas::OFFSETX, y, 2);
	}

	// Draw vectors
	for (auto vector : vectors)
	{
		application->SetColor(vector.GetColor());
		vector.Draw(application, Canvas::OFFSETX + (vector.startingX * Canvas::FIELDWIDTH), Canvas::OFFSETY + Canvas::HEIGHT - (vector.startingY * Canvas::FIELDHEIGHT));
	}

	for (auto matrix : matrixes)
	{
		application->SetColor(defaultColor);
	}

	application->SetColor(defaultColor);
}