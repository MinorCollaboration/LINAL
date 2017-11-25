#include "point.h"
#include "constants.h"

Linal::Point::Point() : xAxis(1), yAxis(1)
{
}

Linal::Point::Point(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
}

Linal::Point::~Point()
{
}

void Linal::Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX + (xAxis * Linal::FIELDWIDTH), offsetY - (yAxis * Linal::FIELDHEIGHT), Point::SIZE, true);
}
