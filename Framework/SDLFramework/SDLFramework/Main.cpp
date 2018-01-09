#include <iostream>
#include <memory>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>

//#include "ExampleGameObject.h"
#include "./Linal/graphical3D/3dpoint.h"

#include "./Linal/camera.hpp"
#include "./Linal/constants.h"
#include "./Linal/matrix.h"
#include "./Linal/graphical2D/canvas.h"

void ScaleObject(Linal::Matrix<Linal::G2D::Point>& matrix, double scaleX, double scaleY)
{
	auto scale = Linal::Get2DScaleMatrix(scaleX, scaleY);
	matrix = scale * matrix;
}

void RotateObject(Linal::Matrix<Linal::G2D::Point>& matrix, double degree)
{
	auto rotate = Linal::Get2DRotateMatrix(degree);
	matrix = rotate * matrix;
}

/*

*/
void RotateObjectOnXAxis(Linal::Matrix<Linal::G3D::Point>& matrix, double degree, double originX, double originY, double originZ)
{
	auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
	auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
	auto rotate = Linal::Get3DRotateXAxisMatrix(degree);

	auto rotrans = rotate * translate;
	auto rotated = rotrans * matrix;
	matrix = revertTranslate * rotated;
}

/*
*/
void RotateObjectOnYAxis(Linal::Matrix<Linal::G3D::Point>& matrix, double degree, double originX, double originY, double originZ)
{
	auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
	auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
	auto rotate = Linal::Get3DRotateYAxisMatrix(degree);

	auto rotated = (rotate * translate) * matrix;
	matrix = revertTranslate * rotated;
}

/*

*/
void RotateObjectOnZAxis(Linal::Matrix<Linal::G3D::Point>& matrix, double degree, double originX, double originY, double originZ)
{
	auto translate = Linal::Get3DTranslateMatrix(-originX, -originY, -originZ);
	auto revertTranslate = Linal::Get3DTranslateMatrix(originX, originY, originZ);
	auto rotate = Linal::Get3DRotateZAxisMatrix(degree);

	auto rotated = (rotate * translate) * matrix;
	matrix = revertTranslate * rotated;
}

void RotateObject(Linal::Matrix<Linal::G2D::Point>& matrix, double degree, double originX, double originY)
{
	auto translate = Linal::Get2DTranslateMatrix(-originX, -originY);
	auto revertTranslate = Linal::Get2DTranslateMatrix(originX, originY);
	auto rotate = Linal::Get2DRotateMatrix(degree);

	auto rotated = (rotate * translate) * matrix;
	matrix = revertTranslate * rotated;
}


int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication(0, 25, 1920, 834);
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}

	#ifdef _DEBUG
		#ifdef _WIN32
			// Initialize memory leak detection.
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		#endif // _WIN32
	#endif
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

	auto canvas { std::unique_ptr<Linal::G2D::Canvas>{ new Linal::G2D::Canvas() } };

	auto spaceship = Linal::Matrix<Linal::G3D::Point>{ 1 };
	spaceship.Set(1, Linal::G3D::Point(0, 0, 0));

	auto cube = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(4, 8, 2);
	auto toprightfront = Linal::G3D::Point(8, 8, 2);
	auto bottomleftfront = Linal::G3D::Point(4, 4, 2);
	auto bottomrightfront = Linal::G3D::Point(8, 4, 2);
	auto topleftback = Linal::G3D::Point(4, 8, 6);
	auto toprightback = Linal::G3D::Point(8, 8, 6);
	auto bottomleftback = Linal::G3D::Point(4, 4, 6);
	auto bottomrightback = Linal::G3D::Point(8, 4, 6);

	cube.Set(1, topleftfront);
	cube.Set(2, toprightfront);
	cube.Set(3, bottomrightfront);
	cube.Set(4, bottomleftfront);
	cube.Set(5, bottomleftback);
	cube.Set(6, bottomrightback);
	cube.Set(7, toprightback);
	cube.Set(8, topleftback);

	auto camera1 = Linal::Camera(0,		0,	 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera2 = Linal::Camera(500,	0,	 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera3 = Linal::Camera(1000,	0,	 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera4 = Linal::Camera(0,		278, 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera5 = Linal::Camera(500,	278, 500, 278, Linal::GetCameraMatrix(1, 10, 10, 1, 1, 1));
	auto camera6 = Linal::Camera(1000,	278, 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera7 = Linal::Camera(0,		556, 500, 278, Linal::GetCameraMatrix(1, 1, 1, -4, 1, 6));
	auto camera8 = Linal::Camera(500,	556, 500, 278, Linal::GetCameraMatrix(1, 1, 1, 1, 1, 3));
	auto camera9 = Linal::Camera(1000,	556, 500, 278, Linal::GetCameraMatrix(1, 1, 1, 5, 1, 6));

	bool debug = true;

	//RotateObjectOnZAxis(cube, 90, 4, 4, 2);

	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

				default:
					break;
				}
			}
		}

		canvas->Draw(application);

		camera1.Draw(application, "LeftBackView");
		camera2.Draw(application, "BackView");
		camera3.Draw(application, "RightBackView");
		camera4.Draw(application, "LeftView");
		camera5.Draw(application, "TopView");
		camera6.Draw(application, "RightView");
		camera7.Draw(application, "LeftFrontView");
		camera8.Draw(application, "FrontView");
		camera9.Draw(application, "RightFrontView");

		RotateObjectOnYAxis(cube, 90 / 30, 6, 6, 4);

		camera1.Draw(application, cube);
		camera2.Draw(application, cube);
		camera3.Draw(application, cube);
		camera4.Draw(application, cube);
		camera5.Draw(application, cube);
		camera6.Draw(application, cube);
		camera7.Draw(application, cube);
		camera8.Draw(application, cube);
		camera9.Draw(application, cube);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	delete application;
	return EXIT_SUCCESS;
}
