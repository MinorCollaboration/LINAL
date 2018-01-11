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
	bool debug = false;
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
	//camera variables
	int eyeX = 0, eyeY = 0, eyeZ = 0;
	int lookAtX = 400, lookAtY = 400, lookAtZ = 400;
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication(0, 25, 600, 600);
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

	//auto canvas { std::unique_ptr<Linal::G2D::Canvas>{ new Linal::G2D::Canvas() } }

	auto spaceship = Linal::Matrix<Linal::G3D::Point>{ 1 };
	spaceship.Set(1, Linal::G3D::Point(0, 0, 0));

	auto canvas = Linal::Matrix<Linal::G3D::Vector>{ 3 };
	auto xLine = Linal::G3D::Vector(1, 2, 3, 4, 5, 6);
	auto yLine = Linal::G3D::Vector(7, 8, 9, 10, 11, 12);
	auto zLine = Linal::G3D::Vector(13, 14, 15, 16, 17, 18);

	canvas = canvas.AddHelpLine();

	canvas.Set(1, xLine);
	canvas.Set(2, yLine);
	canvas.Set(3, zLine);

	auto x = canvas.Get(1);
	auto y = canvas.Get(2);
	auto z = canvas.Get(3);

	auto cube = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(400, 800, 200);
	auto toprightfront = Linal::G3D::Point(800, 800, 200);
	auto bottomleftfront = Linal::G3D::Point(400, 400, 200);
	auto bottomrightfront = Linal::G3D::Point(800, 400, 200);
	auto topleftback = Linal::G3D::Point(400, 800, 600);
	auto toprightback = Linal::G3D::Point(800, 800, 600);
	auto bottomleftback = Linal::G3D::Point(400, 400, 600);
	auto bottomrightback = Linal::G3D::Point(800, 400, 600);

	cube.Set(1, topleftfront);
	cube.Set(2, toprightfront);
	cube.Set(3, bottomleftfront);
	cube.Set(4, bottomrightfront);
	cube.Set(5, bottomleftback);
	cube.Set(6, bottomrightback);
	cube.Set(7, topleftback);
	cube.Set(8, toprightback);

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
				system("cls");
				std::cout << "key pressed " << event.key.keysym.sym << " interperterd as";
				switch (event.key.keysym.sym) {
				case 119:
					std::cout << " w" << std::endl;
					eyeZ += Linal::CAMERASTEP;
					break;
				case 115:
					std::cout << " s" << std::endl;
					eyeZ -= Linal::CAMERASTEP;
					break;
				case 100:
					std::cout << " d" << std::endl;
					eyeX += Linal::CAMERASTEP;
					break;
				case 97:
					std::cout << " a" << std::endl;
					eyeX -= Linal::CAMERASTEP;
					break;
				case 61:
					std::cout << " +" << std::endl;
					eyeY -= Linal::CAMERASTEP;
					break;
				case 45:
					std::cout << " -" << std::endl;
					eyeY += Linal::CAMERASTEP;
					break;
				case SDLK_DOWN:
					std::cout << " down arrow" << std::endl;
					lookAtY -= Linal::CAMERASTEP;
					break;
				case SDLK_UP:
					std::cout << " up arrow" << std::endl;
					lookAtY += Linal::CAMERASTEP;
					break;
				case SDLK_LEFT:
					std::cout << " left arrow" << std::endl;
					lookAtX -= Linal::CAMERASTEP;
					break;
				case SDLK_RIGHT:
					std::cout << " right arrow" << std::endl;
					lookAtX += Linal::CAMERASTEP;
					break;
				case SDLK_ESCAPE:
					application->Quit();
					break;
				default:
					std::cout << "none" << std::endl;
					break;
				}
				std::cout << "Eye (" << eyeX << "," << eyeY << "," << eyeZ << ")" << std::endl;
				std::cout << "LookAt (" << lookAtX << "," << lookAtY << "," << lookAtZ << ")" << std::endl;
			default:
				break;
			}
		}
		auto camera = Linal::Camera(0, 0, 600, 600, Linal::GetCameraMatrix(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ));

		//canvas->Draw(application);

		//camera5.SetCameraMatrix(Linal::GetCameraMatrix(1, frameCount, -15, 1, 1, 1));
		//RotateObjectOnYAxis(cube, 90 / 30, 6, 6, 4);

		camera.Draw(application, "General");

		//RotateObjectOnYAxis(cube, 90 / 30, 6, 6, 4);

		camera.Draw(application, canvas);
		camera.Draw(application, cube);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}

	delete application;
	return EXIT_SUCCESS;
}
