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
	void ScaleObject(double originX, double originY, double originZ,double scaleX, double scaleY, double scaleZ)
	{
		auto translate = Linal::Get3DTranslateMatrix(-originX, -originY,-originZ);
		auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
		auto scale = Linal::Get3DScaleMatrix(scaleX, scaleY, scaleZ);

		moon_matrix = translate * moon_matrix;
		moon_matrix = scale * moon_matrix;
		moon_matrix = revertTranslate * moon_matrix;

	}
	void pulse(double scale) {
		
		if (plus_counter < scale) {
			min_counter = 0;
			ScaleObject(moon_matrix.GetMinX(), moon_matrix.GetMinY(), moon_matrix.GetMinZ(), 1.1, 1.1, 1.1);
			plus_counter++;

		}else if(maxX < moon_matrix.GetMaxX()){
			ScaleObject(moon_matrix.GetMinX(), moon_matrix.GetMinY(), moon_matrix.GetMinZ(), 0.9, 0.9, 0.9);
			min_counter++;
			if (min_counter  == scale) {
				plus_counter = 0;
			}
		}
		else {
			plus_counter = 0;
		}
		
	}

	Linal::Matrix<Linal::G3D::Point> get_moon_matrix() {
		return moon_matrix;
	};

private:
	int plus_counter = 0;
	int min_counter = 0;
	double maxX;
	double maxY;
	double maxZ;
	Linal::Matrix<Linal::G3D::Point> moon_matrix;


};

moon::moon()
{
	moon_matrix = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(1400,1600, 1200);
	auto toprightfront = Linal::G3D::Point(1600, 1600, 1200);
	auto bottomleftfront = Linal::G3D::Point(1400, 1400, 1200);
	auto bottomrightfront = Linal::G3D::Point(1600, 1400, 1200);
	auto topleftback = Linal::G3D::Point(1400, 1600, 1600);
	auto toprightback = Linal::G3D::Point(1600, 1600, 1600);
	auto bottomleftback = Linal::G3D::Point(1400, 1400, 1600);
	auto bottomrightback = Linal::G3D::Point(1600, 1400, 1600);

	moon_matrix.Set(1, topleftfront);
	moon_matrix.Set(2, toprightfront);
	moon_matrix.Set(3, bottomrightfront);
	moon_matrix.Set(4, bottomleftfront);
	moon_matrix.Set(5, bottomleftback);
	moon_matrix.Set(6, bottomrightback);
	moon_matrix.Set(7, toprightback);
	moon_matrix.Set(8, topleftback);

	//set max variable
	maxX = moon_matrix.GetMaxX();
	maxY = moon_matrix.GetMaxY();
	maxZ = moon_matrix.GetMaxZ();

}

moon::~moon()
{
}