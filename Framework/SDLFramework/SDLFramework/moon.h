#pragma once
#include "./Linal/graphical3D/3dpoint.h"

#include "./Linal/camera.hpp"
#include "./Linal/constants.h"
#include "./Linal/matrix.h"
#include "./Linal/graphical2D/canvas.h"
class moon
{
public:
	moon();
	~moon();
	void ScaleObject(double scaleX, double scaleY)
	{
		auto scale = Linal::Get2DScaleMatrix(scaleX, scaleY);
		moon_matrix = scale * moon_matrix;
	}

	Linal::Matrix<Linal::G3D::Point> get_moon_matrix() {
		return moon_matrix;
	};

private:
	Linal::Matrix<Linal::G3D::Point> moon_matrix;


};

moon::moon()
{
	moon_matrix = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(14,16, 12);
	auto toprightfront = Linal::G3D::Point(16, 16, 12);
	auto bottomleftfront = Linal::G3D::Point(14, 14, 12);
	auto bottomrightfront = Linal::G3D::Point(16, 14, 12);
	auto topleftback = Linal::G3D::Point(14, 16, 16);
	auto toprightback = Linal::G3D::Point(16, 16, 16);
	auto bottomleftback = Linal::G3D::Point(14, 14, 16);
	auto bottomrightback = Linal::G3D::Point(16, 14, 16);

	moon_matrix.Set(1, topleftfront);
	moon_matrix.Set(2, toprightfront);
	moon_matrix.Set(3, bottomrightfront);
	moon_matrix.Set(4, bottomleftfront);
	moon_matrix.Set(5, bottomleftback);
	moon_matrix.Set(6, bottomrightback);
	moon_matrix.Set(7, toprightback);
	moon_matrix.Set(8, topleftback);
}

moon::~moon()
{
}