#include <iostream>
#include <memory>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>

#include "ExampleGameObject.h"
#include "canvas.h"
#include "constants.h"
#include "matrix.h"

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

	auto canvas{ std::unique_ptr<Linal::Canvas>{ new Linal::Canvas() } };

	auto topbar		= Linal::Vector(0, 2, 4, 4);
	//auto leftbar	= Linal::Vector(2, 0, 4, 2);
	//auto rightbar	= Linal::Vector(2, 0, 6, 2);
	//auto bottombar	= Linal::Vector(0, 2, 4, 2);

	//auto square = Linal::Matrix<Linal::Vector>{ 2, 2 };
	//square.Set(1, 1, topbar); // .Set(1, 2, leftbar);
	//square.Set(2, 1, bottombar).Set(2, 2, rightbar);

	auto square = Linal::Matrix<Linal::Point>{ 2, 2 };
	auto topleft = Linal::Point(2, 6);
	auto topright = Linal::Point(6, 6);
	auto bottomleft = Linal::Point(2, 2);
	auto bottomright = Linal::Point(6, 2);

	square.Set(1, 1, topleft).Set(1, 2, topright);
	square.Set(2, 1, bottomleft).Set(2, 2, bottomright);

	auto scale = Linal::GetScaleMatrix(1.1, 1.1);
	
	auto scaled = scale * square;

	auto a = Linal::GetTranslateMatrix(0.1, 0.1);
	Linal::Matrix<float> b = Linal::Matrix<float>{ 3, 4 };

	b.Set(1, 1, 3).Set(1, 2, 4).Set(1, 3, 6).Set(1, 4, 1);
	b.Set(2, 1, 2).Set(2, 2, 1).Set(2, 3, 7).Set(2, 4, 5);
	b.Set(3, 1, 1).Set(3, 2, 1).Set(3, 3, 1).Set(3, 4, 1);

	auto c = a * b;

	//auto testpoint = Linal::Point(1, 1);
	//auto extratest = Linal::Point(5, 7);

	/*
	canvas->points.push_back(testpoint);
	canvas->points.push_back(extratest);

	 auto vector1 = Linal::Vector(-3, 0, 18, 18);
	 auto vector2 = Linal::Vector(-1, -5, 18, 18);

	 auto vectorSum = vector1 + vector2;

	 canvas->vectors.push_back(vector1);
	 canvas->vectors.push_back(vector2);

	 //auto decreased = vectorSum / 2;
	 //auto increased = vectorSum * 2;

	 canvas->vectors.push_back(vectorSum);
	 */
	 //canvas->vectors.push_back(decreased);
	 //canvas->vectors.push_back(increased);

	//while (true){}
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
		c.Draw(application, Linal::OFFSETX + 200, Linal::OFFSETY + 200);

		square.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	delete application;
	return EXIT_SUCCESS;
}
