#include "cube.h"

using namespace Spaceshooter;

Cube::Cube(double offsetX, double offsetY, double offsetZ, double size)
{
	points = Linal::Matrix<Linal::G3D::Point>{ 8 };

	auto topleftfront		= Linal::G3D::Point(offsetX, offsetY + size, offsetZ);
	auto toprightfront		= Linal::G3D::Point(offsetX + size, offsetY + size, offsetZ);
	auto bottomleftfront	= Linal::G3D::Point(offsetX, offsetY, offsetZ);
	auto bottomrightfront	= Linal::G3D::Point(offsetX + size, offsetY, offsetZ);
	auto topleftback		= Linal::G3D::Point(offsetX, offsetY + size, offsetZ + size);
	auto toprightback		= Linal::G3D::Point(offsetX + size, offsetY + size, offsetZ + size);
	auto bottomleftback		= Linal::G3D::Point(offsetX, offsetY, offsetZ + size);
	auto bottomrightback	= Linal::G3D::Point(offsetX + size, offsetY, offsetZ + size);

	points.Set(1, topleftfront);
	points.Set(2, toprightfront);
	points.Set(3, bottomleftfront);
	points.Set(4, bottomrightfront);
	points.Set(5, topleftback);
	points.Set(6, toprightback);
	points.Set(7, bottomleftback);
	points.Set(8, bottomrightback);

	connections = Linal::Matrix<Linal::G3D::Vector>{ 8 };

	auto fronttop = Linal::G3D::GetConnection(topleftfront, toprightfront);
	auto frontright = Linal::G3D::GetConnection(toprightfront, bottomrightfront);
	auto frontbottom = Linal::G3D::GetConnection(bottomrightfront, bottomleftfront);
	auto frontleft = Linal::G3D::GetConnection(bottomleftfront, topleftfront);

	auto backtop = Linal::G3D::GetConnection(topleftback, toprightback);
	auto backright = Linal::G3D::GetConnection(toprightback, bottomrightback);
	auto backbottom = Linal::G3D::GetConnection(bottomrightback, bottomleftback);
	auto backleft = Linal::G3D::GetConnection(bottomleftback, topleftback);

	/* *
	auto topleft = Linal::G3D::GetConnection(topleftfront, topleftback);
	auto topright = Linal::G3D::GetConnection(toprightfront, toprightback);
	auto bottomright = Linal::G3D::GetConnection(bottomrightfront, bottomrightback);
	auto bottomleft = Linal::G3D::GetConnection(bottomleftfront, bottomleftback);
	/* */

	connections.Set(1, fronttop);
	/* */
	connections.Set(2, frontright);
	connections.Set(3, frontbottom);
	connections.Set(4, frontleft);

	connections.Set(5, backtop);
	connections.Set(6, backright);
	connections.Set(7, backbottom);
	connections.Set(8, backleft);

	/* *
	connections.Set(9, topleft);
	connections.Set(10, topright);
	connections.Set(11, bottomright);
	connections.Set(12, bottomleft);
	/* */
}

Linal::Matrix<Linal::G3D::Point> Spaceshooter::Cube::GetPolygons() const
{
	return points;
}

Linal::Matrix<Linal::G3D::Vector> Spaceshooter::Cube::GetConnections() const
{
	return connections;
}
