#pragma once 

#include "linal/matrix.h"

#ifndef SDLFRAMEWORK_SPACESHOOTER_CUBE
#define SDLFRAMEWORK_SPACESHOOTER_CUBE

namespace Spaceshooter
{
	class Cube
	{
	private:
		Linal::Matrix<Linal::G3D::Point> points;
		Linal::Matrix<Linal::G3D::Vector> connections;
	public:
		Cube(double offsetX, double offsetY, double offsetZ, double size);

		Linal::Matrix<Linal::G3D::Point> GetPolygons() const;
		Linal::Matrix<Linal::G3D::Vector> GetConnections() const;
	private:
	};
}

#endif