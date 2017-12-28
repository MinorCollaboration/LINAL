#pragma once 

#ifndef SDLFRAMEWORK_LINAL_INPRODUCT
#define SDLFRAMEWORK_LINAL_INPRODUCT

#include <memory>
#include <iomanip>
#include <math.h>
#include <typeinfo>

#include "./graphical3D/3dpoint.h"
#include "./graphical3D/3dvector.h"

namespace Linal
{
	static double GetInProduct(Linal::G3D::Point a, Linal::G3D::Point b)
	{
		return a.xAxis * b.xAxis + a.yAxis * b.yAxis + a.zAxis * b.zAxis;
	}

	static double GetInProduct(Linal::G3D::Vector a, Linal::G3D::Point b)
	{
		return a.xAxis * b.xAxis + a.yAxis * b.yAxis + a.zAxis * b.zAxis;
	}

	static Linal::G3D::Point GetOutProduct(Linal::G3D::Point a, Linal::G3D::Point b)
	{
		return Linal::G3D::Point(
			a.yAxis * b.zAxis - a.zAxis * b.yAxis,
			a.zAxis * b.xAxis - a.xAxis * b.yAxis,
			a.xAxis * b.yAxis - a.yAxis * b.xAxis
		);
	}

	static Linal::G3D::Vector GetOutProduct(Linal::G3D::Vector a, Linal::G3D::Vector b)
	{
		return Linal::G3D::Vector(
			a.yAxis * b.zAxis - a.zAxis * b.yAxis,
			a.zAxis * b.xAxis - a.xAxis * b.yAxis,
			a.xAxis * b.yAxis - a.yAxis * b.xAxis
		);
	}
}

#endif