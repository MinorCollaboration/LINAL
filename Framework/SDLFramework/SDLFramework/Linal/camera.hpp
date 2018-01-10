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
		Camera(int startX, int startY, int width, int height, Matrix<double> cameraMatrix);
		~Camera();

		Camera& SetCameraMatrix(Linal::Matrix<double> cM);

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
		Matrix<double> cameraMatrix = Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3);
	};

	Camera::Camera(int startX, int startY, int width, int height) : startX(startX), startY(startY), width(width), height(height)
	{
		cameraMatrix = Linal::GetCameraMatrix(1, 1, -15, 1, 1, 1);
	}

	Camera::Camera(int startX, int startY, int width, int height, Matrix<double> cameraMatrix) : startX(startX), startY(startY), width(width), height(height), cameraMatrix(cameraMatrix)
	{
	}

	Camera::~Camera() {
	}

	Camera& Camera::SetCameraMatrix(Linal::Matrix<double> cM)
	{
		cameraMatrix = cM;

		return *this;
	}

	void Camera::Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Point> wereldmatrix)
	{
		auto projectiematrix = Linal::GetPerspectiveMatrix(1, 100, 90);
		//wereldmatrix = wereldmatrix.AddHelpLine();

		//auto translatie = Linal::Get3DTranslateMatrix(-25, 6, 0);
		//wereldmatrix = translatie * wereldmatrix;

		auto weergavePunten = projectiematrix * cameraMatrix * wereldmatrix;

		// DOESN'T WORK ANYMORE DUE HELPLINE CHANGES
		auto translatie = Linal::Get3DTranslateMatrix(25, 6, 0);
		//weergavePunten = translatie * weergavePunten;

		for (int index = 1; index <= wereldmatrix.GetWidth(); index++)
		{
			auto p = weergavePunten.Get(index);

			auto w = weergavePunten.matrix.at(weergavePunten.ConvertToIndex(4, index));
			auto x = (width  / 2) + ((p.xAxis + 1) / w) * width * 0.5;
			auto y = (height / 2) + ((p.yAxis + 1) / w) * height * 0.5;
			auto z = -p.zAxis;

			//double max = weergavePunten.GetMaxZ();
			if (weergavePunten.matrix.at(weergavePunten.ConvertToIndex(4, index)) >= 0)
			{
				//application->DrawCircle(startX + (p.xAxis  * (Linal::FIELDWIDTH / 2)), (startY + height) - (p.yAxis * (Linal::FIELDHEIGHT / 2)), Linal::POINTSIZE, true);
				//application->DrawCircle(startX +  width / 2, startY + height / 2, Linal::POINTSIZE, true);
				application->DrawCircle(startX + x, startY - y, Linal::POINTSIZE, true);
			}
		}
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