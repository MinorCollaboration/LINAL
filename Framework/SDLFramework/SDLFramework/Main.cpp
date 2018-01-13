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
#include "spaceship.h"

#include "./cube.h"

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
	//ship
	spaceship ship;

	//camera variables
	int eyeX = 0, eyeY = 0, eyeZ = 0;
	int lookAtX = 400, lookAtY = 400, lookAtZ = 400;
	int camera_x = 0;
	int camera_y = 0;
	int camera_z = 4;
	int camera_move_x = 1;
	int camera_move_y = 1;
	int camera_move_z = 1;
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
	auto xLine = Linal::G3D::Vector(99999, 0, 0,
										0, 0, 0);
	auto yLine = Linal::G3D::Vector(0, 99999, 0,
										0, 0, 0);
	auto zLine = Linal::G3D::Vector(0, 0, 99999,
										0, 0, 0);

	/*
	1 - 0 - 0 - 0 - 0 - 0
	0 - 0 - 1 - 0 - 0 - 0
	0 - 0 - 0 - 0 - 1 - 0
	/* */

	canvas.Set(1, xLine);
	canvas.Set(2, yLine);
	canvas.Set(3, zLine);

	auto cube = Spaceshooter::Cube(200, 200, -200, 400);

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
					camera_y++;
					break;
				case 45:
					std::cout << " -" << std::endl;
					eyeY += Linal::CAMERASTEP;
					camera_y--;
					break;
				case SDLK_DOWN:
					std::cout << " down arrow" << std::endl;
					lookAtY -= Linal::CAMERASTEP;
					break;
				case SDLK_UP:
					std::cout << "move ship" << std::endl;
					lookAtY += Linal::CAMERASTEP;
					ship.moveObject(1);
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
				case SDLK_e:
					std::cout << "min" << std::endl;
					camera_move_x--;
					break;
				case SDLK_r:
					std::cout << "min" << std::endl;
					camera_move_y--;
					break;
				case SDLK_t:
					std::cout << "min" << std::endl;
					camera_move_z--;
					break;
				case SDLK_q:
					std::cout << "rotate ship" << std::endl;
					ship.RotateObjectOnXAxis( 90 / 30, 6, 6, 4);
					break;
				}
				/* *
				std::cout << "Eye (" << camera_x << "," << camera_y << "," << camera_z << ")" << std::endl;
				std::cout << "LookAt (" << camera_move_x << "," << camera_move_y << "," << camera_move_z << ")" << std::endl;
				/* */
				std::cout << "Eye (" << eyeX << "," << eyeY << "," << eyeZ << ")" << std::endl;
				std::cout << "LookAt (" << lookAtX << "," << lookAtY << "," << lookAtZ << ")" << std::endl;
				/* */
			default:
				break;
			}
		}
		auto camera = Linal::Camera(0, 0, 600, 600, Linal::GetCameraMatrix(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ));

		//canvas->Draw(application);
		//auto camera = Linal::Camera(0, 0, 600, 600, Linal::GetCameraMatrix(camera_x, camera_y, camera_z, camera_move_x, camera_move_y, camera_move_z));

		//camera5.SetCameraMatrix(Linal::GetCameraMatrix(1, frameCount, -15, 1, 1, 1));
		//RotateObjectOnYAxis(cube, 90 / 30, 6, 6, 4);

		camera.Draw(application, "General");

		//RotateObjectOnYAxis(cube, 90 / 30, 6, 6, 4);
		auto matrix = ship.get_ship_matrix();

		camera.Draw(application, canvas);
		camera.Draw(application, cube.GetPolygons());
		camera.Draw(application, cube.GetConnections());
		//camera.Draw(application, matrix);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}

	delete application;
	return EXIT_SUCCESS;
}
