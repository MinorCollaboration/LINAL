#include "point.h"

Linal::Point::Point(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis)
{
}

Linal::Point::~Point()
{
}

void Linal::Point::Draw(FWApplication *& application, int offsetX, int offsetY)
{
	application->DrawCircle(offsetX, offsetY, Point::SIZE, true);
}
