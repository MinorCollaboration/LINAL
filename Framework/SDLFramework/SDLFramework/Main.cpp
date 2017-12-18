#include <iostream>
#include <memory>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>

//#include "ExampleGameObject.h"
#include "./Linal/graphical3D/point.h"
#include "./Linal/graphical3D/point.cpp"
#include "./Linal/graphical3D/vector.h"
#include "./Linal/graphical3D/vector.cpp"
#include "./Linal/constants.h"
#include "./matrix.h"
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

void RotateObject(Linal::Matrix<Linal::G3D::Point>& matrix, double degree)
{

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
	auto application = new FWApplication();
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

	auto canvas{ std::unique_ptr<Linal::G2D::Canvas>{ new Linal::G2D::Canvas() } };

	/******************************************
	 *             Scaling Matrix             *
	 ******************************************/

	// With Ints/doubles
	/* *
	auto a = Linal::Get2DScaleMatrix(1.2, 1.1);
	auto b = Linal::Matrix<double>{ 2, 4 };

	b.Set(1, 1, 3).Set(1, 2, 4).Set(1, 3, 6).Set(1, 4, 1);
	b.Set(2, 1, 2).Set(2, 2, 1).Set(2, 3, 7).Set(2, 4, 5);

	/* *
	auto c = a * b;
	/* */

	// With Points
	/* */
	auto square = Linal::Matrix<Linal::G2D::Point>{ 6 };
	auto topleft = Linal::G2D::Point(2, 5);
	auto topcenter = Linal::G2D::Point(4, 5);
	auto topright = Linal::G2D::Point(6, 5);
	auto bottomleft = Linal::G2D::Point(2, 2);
	auto bottomcenter = Linal::G2D::Point(4, 2);
	auto bottomright = Linal::G2D::Point(6, 2);

	square.Set(1, topleft);
	square.Set(2, topcenter);
	square.Set(3, topright);
	square.Set(4, bottomright);
	square.Set(5, bottomcenter);
	square.Set(6, bottomleft);
	/* */

	auto cube = Linal::Matrix<Linal::G3D::Point>{ 8 };
	auto topleftfront = Linal::G3D::Point(4, 8, 2);
	auto toprightfront = Linal::G3D::Point(8, 8, 2);
	auto bottomleftfront = Linal::G3D::Point(4, 4, 2);
	auto bottomrightfront = Linal::G3D::Point(8, 4, 2);
	auto topleftback = Linal::G3D::Point(4, 8, 4);
	auto toprightback = Linal::G3D::Point(8, 8, 4);
	auto bottomleftback = Linal::G3D::Point(4, 4, 4);
	auto bottomrightback = Linal::G3D::Point(8, 4, 4);

	cube.Set(1, topleftfront);
	cube.Set(2, toprightfront);
	cube.Set(3, bottomleftfront);
	cube.Set(4, bottomrightfront);
	cube.Set(5, topleftback);
	cube.Set(6, toprightback);
	cube.Set(7, bottomleftback);
	cube.Set(8, bottomrightback);

	bool debug = true;

	/******************************************
	*          End of scaling matrix          *
	******************************************/

	/******************************************
	 *            Translate Matrix            *
	 ******************************************/
	/* *
	auto a = Linal::GetTranslateMatrix(0.1, 0.1);
	Linal::Matrix<double> b = Linal::Matrix<float>{ 3, 4 };

	b.Set(1, 1, 3).Set(1, 2, 4).Set(1, 3, 6).Set(1, 4, 1);
	b.Set(2, 1, 2).Set(2, 2, 1).Set(2, 3, 7).Set(2, 4, 5);
	b.Set(3, 1, 1).Set(3, 2, 1).Set(3, 3, 1).Set(3, 4, 1);

	auto c = a * b;
	/* */

	/******************************************
	 *        End of translate Matrix         *
	 *****************************************/

	/******************************************
	 *             Multiple Matrix            *
	 ******************************************/
	
	/* *
	auto a = Linal::Matrix<int>{ 2, 2 };
	auto b = Linal::Matrix<int>{ 2, 3 };

	a.Set(1, 1, 4).Set(1, 2, 1);
	a.Set(2, 1, 2).Set(2, 2, 3);

	b.Set(1, 1, 3).Set(1, 2, 0).Set(1, 3, 4);
	b.Set(2, 1, 2).Set(2, 2, 5).Set(2, 3, 1);

	auto c = a * b;
	/* */

	/******************************************
	 *         End of tultiple Matrix         *
	 ******************************************/

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
		/*     numeric matrix    *
		a.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT - 55);
		b.Draw(application, Linal::OFFSETX + 75, Linal::OFFSETY + Linal::HEIGHT - 55);
		c.Draw(application, Linal::OFFSETX + 200, Linal::OFFSETY + Linal::HEIGHT - 55);
		/* End of numeric matrix */

		//RotateObject(square, 90/30, 3.5, 4);
		//RotateObject(square, -90);

		//square.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);
		//square.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);
		cube.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	delete application;
	return EXIT_SUCCESS;
}
