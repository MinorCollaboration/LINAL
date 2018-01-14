#pragma once
#include "./Linal/graphical3D/3dpoint.h"

#include "./Linal/camera.hpp"
#include "./Linal/constants.h"
#include "./Linal/matrix.h"
#include "./Linal/graphical2D/canvas.h"

class spaceship
{
public:

	spaceship();
	~spaceship();

	void RotateObjectOnXAxis( double degree, double originX, double originY, double originZ)
	{
		auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
		auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
		auto rotate = Linal::Get3DRotateXAxisMatrix(degree);

		auto rotrans = rotate * translate;
		auto rotated = rotrans * ship_matrix;
		ship_matrix = revertTranslate * rotated;
	}
	void RotateObjectOnYAxis( double degree, double originX, double originY, double originZ)
	{
		auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
		auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
		auto rotate = Linal::Get3DRotateYAxisMatrix(degree);

		auto rotated = (rotate * translate) * ship_matrix;
		ship_matrix = revertTranslate * rotated;
	}
	void RotateObject(double degree)
	{
		auto rotate = Linal::Get2DRotateMatrix(degree);
		ship_matrix = rotate * ship_matrix;

	}
	void moveObject (double originX){
		auto translate = Linal::Get3DTranslateMatrix(originX, ship_matrix.GetMinX(), ship_matrix.GetMinY());
		ship_matrix = translate * ship_matrix;
	}
	
	

	/*
	*/
	

	Linal::Matrix<Linal::G3D::Point> get_ship_matrix() {
		return ship_matrix;
};

	void move_ship() {
		
	

	};
private:
	Linal::Matrix<Linal::G3D::Point> ship_matrix;

};

spaceship::spaceship()
{
	ship_matrix = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(4, 6, 2);
	auto toprightfront = Linal::G3D::Point(6, 6, 2);
	auto bottomleftfront = Linal::G3D::Point(4, 4, 2);
	auto bottomrightfront = Linal::G3D::Point(6, 4, 2);
	auto topleftback = Linal::G3D::Point(4, 6, 6);
	auto toprightback = Linal::G3D::Point(6, 6, 6);
	auto bottomleftback = Linal::G3D::Point(4, 4, 6);
	auto bottomrightback = Linal::G3D::Point(6, 4, 6);

	ship_matrix.Set(1, topleftfront);
	ship_matrix.Set(2, toprightfront);
	ship_matrix.Set(3, bottomrightfront);
	ship_matrix.Set(4, bottomleftfront);
	ship_matrix.Set(5, bottomleftback);
	ship_matrix.Set(6, bottomrightback);
	ship_matrix.Set(7, toprightback);
	ship_matrix.Set(8, topleftback);
}

spaceship::~spaceship()
{
}