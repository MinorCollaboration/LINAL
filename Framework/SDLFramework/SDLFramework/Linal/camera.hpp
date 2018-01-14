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
		void RotateObjectOnXAxis(double degree, double originX, double originY, double originZ)
		{
			auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
			auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
			auto rotate = Linal::Get3DRotateXAxisMatrix(degree);

			auto rotrans = rotate * translate;
			auto rotated = rotrans * cameraMatrix;
			cameraMatrix = revertTranslate * rotated;
		}
		Camera(int startX, int startY, int width, int height);
		Camera(int startX, int startY, int width, int height, Matrix<double> cameraMatrix);
		~Camera();
		Matrix<double>  get_camera_matrix();


		Camera& SetCameraMatrix(Linal::Matrix<double> cM);

		void Draw(FWApplication*& application);
		void Draw(FWApplication*& application, std::string label);
		void Draw(FWApplication*& application, Linal::G3D::Point p);
		void Draw(FWApplication*& application, Linal::G3D::Vector v);

		void Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Point> m);
		void Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Vector> m);

		

	private:
		int width;
		int height;
		int startX;
		int startY;
		Matrix<double> cameraMatrix = Linal::GetCameraMatrix(1, 1, 1, 4, 4, 4);
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

	Matrix<double> Camera::get_camera_matrix() {
		return cameraMatrix;
	}

	Camera& Camera::SetCameraMatrix(Linal::Matrix<double> cM)
	{
		cameraMatrix = cM;

		return *this;
	}

	void Camera::Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Point> wereldmatrix)
	{
		auto projectiematrix = Linal::GetPerspectiveMatrix(1, 100, 90);
		auto weergavePunten = projectiematrix * cameraMatrix * wereldmatrix;

		for (int index = 1; index <= weergavePunten.GetWidth(); index++)
		{
			auto p = weergavePunten.Get(index);

			auto w = weergavePunten.matrix.at(weergavePunten.ConvertToIndex(4, index));
			auto x = (width  / 2) + ((p.xAxis + 1) / w) * width * 0.5;
			auto y = (height / 2) + ((p.yAxis + 1) / w) * height * 0.5;
			//auto z = -p.zAxis;

			if (w >= 0) {
				//application->DrawCircle(startX + (p.xAxis  * (Linal::FIELDWIDTH / 2)), (startY + height) - (p.yAxis * (Linal::FIELDHEIGHT / 2)), Linal::POINTSIZE, true);
				application->DrawCircle(startX + x, (startY + height) - y, Linal::POINTSIZE, true);
			}
		}
	}

	void Camera::Draw(FWApplication*& application, Linal::Matrix<Linal::G3D::Vector> wereldmatrix)
	{
		auto projectiematrix = Linal::GetPerspectiveMatrix(1, 100, 90);
		auto weergavePunten = projectiematrix * cameraMatrix * wereldmatrix;

		for (int index = 1; index <= weergavePunten.GetWidth(); index++)
		{
			auto p = weergavePunten.Get(index);

			auto w = weergavePunten.matrix.at(weergavePunten.ConvertToIndex((index * 2) - 1, 4));
			auto x = (width / 2) + ((p.xAxis + 1) / w) * width * 0.5;
			auto y = (height / 2) + ((p.yAxis + 1) / w) * height * 0.5;

			auto ow = weergavePunten.matrix.at(weergavePunten.ConvertToIndex((index * 2), 4));
			auto ox = (width / 2) + ((p.startingX + 1) / ow) * width * 0.5;
			auto oy = (height / 2) + ((p.startingY + 1) / ow) * height * 0.5;
			//auto z = -p.zAxis;

			if (w >= 0 || ow >= 0) {
				//application->DrawCircle(startX + (p.xAxis  * (Linal::FIELDWIDTH / 2)), (startY + height) - (p.yAxis * (Linal::FIELDHEIGHT / 2)), Linal::POINTSIZE, true);
				//application->DrawLine(startX + x, (startY + height) - y, startX + (x + ox), (startY + height) - (y + oy), 2);

				auto startingX = startX + ox;
				auto startingY = (startY + height) - oy;

				auto finalX = startX + x;
				auto finalY = (startY + height) - y;

				application->DrawLine(startingX, startingY, startingX + finalX, startingY - finalY);
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

	void Camera::Draw(FWApplication *& application, Linal::G3D::Point p)
	{
		auto wereldmatrix = Linal::Matrix<Linal::G3D::Point>(1);
		wereldmatrix.Set(1, p);
		auto projectiematrix = Linal::GetPerspectiveMatrix(1, 100, 90);
		auto weergavePunten = projectiematrix * cameraMatrix * wereldmatrix;

		for (int index = 1; index <= weergavePunten.GetWidth(); index++)
		{
			auto p = weergavePunten.Get(index);

			auto w = weergavePunten.matrix.at(weergavePunten.ConvertToIndex(4, index));
			auto x = (width / 2) + ((p.xAxis + 1) / w) * width * 0.5;
			auto y = (height / 2) + ((p.yAxis + 1) / w) * height * 0.5;

			if (w >= 0) {
				application->DrawCircle(startX + x, (startY + height) - y, Linal::POINTSIZE, true);
			}
		}
	}
}

#endif