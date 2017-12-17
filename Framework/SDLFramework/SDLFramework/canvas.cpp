#include "canvas.h"
#include "constants.h"

using namespace Linal::G2D;

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Linal::G2D::Canvas::Draw(FWApplication*& application)
{
	auto defaultColor = Color(127, 127, 127, 255);

	application->SetColor(Color(0, 0, 0, 255));
	application->DrawLine(Linal::OFFSETX, Linal::OFFSETY, Linal::OFFSETX, Linal::HEIGHT + Linal::OFFSETY, 5);
	application->DrawLine(Linal::OFFSETX, Linal::HEIGHT + Linal::OFFSETY, Linal::WIDTH + Linal::OFFSETX, Linal::HEIGHT + Linal::OFFSETY, 5);

	// Draw the vertical lines
	application->SetColor(defaultColor);
	for (int x = Linal::OFFSETX + Linal::FIELDWIDTH; x <= Linal::WIDTH + Linal::OFFSETX; x += Linal::FIELDWIDTH)
	{
		application->DrawLine(x, Linal::HEIGHT + Linal::OFFSETY, x, Linal::OFFSETY, 2);
	}

	// Draw the horizontal lines
	application->SetColor(defaultColor);
	for (int y = Linal::OFFSETY + Linal::HEIGHT - Linal::FIELDHEIGHT; y >= Linal::OFFSETY; y -= Linal::FIELDHEIGHT)
	{
		application->DrawLine(Linal::WIDTH + Linal::OFFSETX, y, Linal::OFFSETX, y, 2);
	}

	// Draw vectors
	for (auto vector : vectors)
	{
		application->SetColor(vector.GetColor());
		vector.Draw(application, Linal::OFFSETX + (vector.startingX * Linal::FIELDWIDTH), Linal::OFFSETY + Linal::HEIGHT - (vector.startingY * Linal::FIELDHEIGHT));
	}
	
	application->SetColor(Color(0, 0, 255, 255));
	for (auto point : points)
	{
		point.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);
	}

	application->SetColor(defaultColor);
}