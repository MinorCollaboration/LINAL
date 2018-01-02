#pragma once 

#ifndef SDLFRAMEWORK_LINAL_CAMERA
#define SDLFRAMEWORK_LINAL_CAMERA

#include <memory>
#include <iomanip>
#include <math.h>
#include <typeinfo>

#include "../FWApplication.h"
#include "./constants.h"
#include "./matrix.h"
#include "./graphical3D/3dpoint.h"
#include "./graphical2D/point.h"

namespace Linal
{
	class Camera
	{
	public:
		Camera(int startX, int startY, int width, int height);
		Camera(int startX, int startY, int width, int height, Matrix<double> rotationMatrix);
		~Camera();

		void Draw(FWApplication*& application);
		void Draw(FWApplication*& application, std::string label);
		void Draw(FWApplication*& application, Linal::G3D::Point p);
		void Draw(FWApplication*& application, Linal::G3D::Vector v);

		void Draw(FWApplication*& application, Linal::Matrix<Linal::G2D::Point> m);
		void Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Point> m);

	private:
		int width;
		int height;
		int startX;
		int startY;
		Matrix<double> rotationMatrix = Linal::Get3DRotateXAxisMatrix(0);
	};

	Camera::Camera(int startX, int startY, int width, int height) : startX(startX), startY(startY), width(width), height(height)
	{
		rotationMatrix = Linal::Get3DRotateXAxisMatrix(0);
	}

	Camera::Camera(int startX, int startY, int width, int height, Matrix<double> rotationMatrix) : startX(startX), startY(startY), width(width), height(height), rotationMatrix(rotationMatrix)
	{
	}

	Camera::~Camera() {
	}



	void Camera::Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Point> wereldmatrix)
	{
		auto projectiematrix = Linal::GetPerspectiveMatrix(1, 15, 90);
		auto cameramatrix	 = Linal::GetCameraMatrix(1, 1, 1, 2, 2, 2);

		auto newwereld = wereldmatrix.AddHelpLine();

		auto weergavePunten = projectiematrix * cameramatrix * newwereld;

		for (int index = 1; index <= wereldmatrix.GetWidth(); index++)
		{
			auto p = weergavePunten.Get(index);

			auto x = (width  / 2) + ((p.xAxis + 1) / 0) * width * 0.5;
			auto y = (height / 2) + ((p.yAxis + 1) / 1) * height * 0.5;

			//double max = weergavePunten.GetMaxZ();
			//if (p.zAxis != max);
			//{
				application->DrawCircle(startX + (p.xAxis * (Linal::FIELDWIDTH / 2)), (startY + height) - (p.yAxis * (Linal::FIELDHEIGHT / 2)), Linal::POINTSIZE, true);
			//}
		}

		/*double	midX{ ((m.GetMaxX() - m.GetMinX()) / 2) + m.GetMinX() },
				midY{ ((m.GetMaxY() - m.GetMinY()) / 2) + m.GetMinY() },
				midZ{ ((m.GetMaxZ() - m.GetMinZ()) / 2) + m.GetMinZ() };

		auto translate = Linal::Get3DTranslateMatrix(-midX, -midY, -midZ ) * m;
 
		auto changedView = rotationMatrix * translate;
		auto translateBack = Linal::Get3DTranslateMatrix(+midX, +midY, +midZ) * changedView;

		auto movedView = Linal::Get3DTranslateMatrix(17, 10, 0) * changedView;
		for (int index = 1; index <= m.GetWidth(); index++)
		{
			auto p = movedView.Get(index);

			double max = movedView.GetMaxZ();
			if (p.zAxis != max)
			{
				application->DrawCircle(startX + (p.xAxis * (Linal::FIELDWIDTH / 2)), (startY + height) - (p.yAxis * (Linal::FIELDHEIGHT / 2)), Linal::POINTSIZE, true);
			}
		}*/
	}

	void Camera::Draw(FWApplication*& application) {
		application->SetColor(Color(255, 0, 0, 255));
		application->DrawRect(startX, startY, width, height, true);

		application->SetColor(Color(0, 0, 0, 255));
		application->DrawLine(startX, startY, startX + width, startY);
		application->DrawLine(startX, startY + height, startX + width, startY + height);

		application->DrawLine(startX, startY, startX, startY + height);
		application->DrawLine(startX + width, startY, startX + width, startY + height);
	}

	void Camera::Draw(FWApplication*& application, std::string label) {
		Draw(application);

		application->SetColor(Color(0, 0, 0, 255));
		application->DrawText(label, startX + (width / 2), startY + height - 10);
	}
}

#endif