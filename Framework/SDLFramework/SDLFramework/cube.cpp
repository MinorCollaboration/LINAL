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

	connections = Linal::Matrix<Linal::G3D::Vector>{ 12 };

	connections.Set(1, Linal::G3D::GetConnection(topleftfront, toprightfront));
	connections.Set(2, Linal::G3D::GetConnection(toprightfront, bottomrightfront));
	connections.Set(3, Linal::G3D::GetConnection(bottomrightfront, bottomleftfront));
	connections.Set(4, Linal::G3D::GetConnection(bottomleftfront, topleftfront));

	connections.Set(5, Linal::G3D::GetConnection(topleftback, toprightback));
	connections.Set(6, Linal::G3D::GetConnection(toprightback, bottomrightback));
	connections.Set(7, Linal::G3D::GetConnection(bottomrightback, bottomleftback));
	connections.Set(8, Linal::G3D::GetConnection(bottomleftback, topleftback));

	connections.Set(9, Linal::G3D::GetConnection(topleftfront, topleftback));
	connections.Set(10, Linal::G3D::GetConnection(toprightfront, toprightback));
	connections.Set(11, Linal::G3D::GetConnection(bottomrightfront, bottomrightback));
	connections.Set(12, Linal::G3D::GetConnection(bottomleftfront, bottomleftback));
}

Linal::Matrix<Linal::G3D::Point> Spaceshooter::Cube::GetPolygons() const
{
	return points;
}

Linal::Matrix<Linal::G3D::Vector> Spaceshooter::Cube::GetConnections() const
{
	return connections;
}
