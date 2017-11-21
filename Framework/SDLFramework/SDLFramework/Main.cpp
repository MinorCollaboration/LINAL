#include <iostream>
#include <memory>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>

#include "ExampleGameObject.h"
#include "canvas.h"
#include "matrix.hpp"

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

	// Dancing cow
	//ExampleGameObject *example = new ExampleGameObject();
	//application->AddRenderable(example);
	auto canvas{ std::unique_ptr<Linal::Canvas>{ new Linal::Canvas() } };

	/*Linal::Matrix<int>* a = new Linal::Matrix<int>(2, 2);
	Linal::Matrix<int>* b = new Linal::Matrix<int>(3, 2);

	a->Set(1, 1, 4)->Set(1, 2, 1);
	a->Set(2, 1, 2)->Set(2, 2, 3);

	b->Set(1, 1, 3)->Set(1, 2, 0)->Set(1, 3, 4);
	b->Set(2, 1, 2)->Set(2, 2, 5)->Set(2, 3, 1);

	auto c = a->operator*(*b);*/

	auto a = Linal::GetTranslateMatrix();
	auto b = new Linal::Matrix<float>(3, 4);

	b->Set(1, 1, 3)->Set(1, 2, 4)->Set(1, 3, 6)->Set(1, 4, 1);
	b->Set(2, 1, 2)->Set(2, 2, 1)->Set(2, 3, 7)->Set(2, 4, 5);
	b->Set(3, 1, 1)->Set(3, 2, 1)->Set(3, 3, 1)->Set(3, 4, 1);

	auto c = a->operator*(*b);

	auto testpoint = new Linal::Point(1, 1);
	auto extratest = new Linal::Point(5, 7);

	canvas->points.push_back(*testpoint);
	canvas->points.push_back(*extratest);

	//canvas->matrixes.push_back(*matrix);

	//canvas->matrixes

	 /*auto vector1 = std::unique_ptr<Linal::Vector>{ new Linal::Vector(-3, 0, 10, 10) };
	 auto vector2 = std::unique_ptr<Linal::Vector>{ new Linal::Vector(-1, -5, 10, 10) };

	 auto vectorSum = *vector1 + *vector2;

	 canvas->vectors.push_back(*vector1);
	 canvas->vectors.push_back(*vector2);

	 //auto decreased = vectorSum / 2;
	 //auto increased = vectorSum * 2;

	 canvas->vectors.push_back(vectorSum);*/
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
		
		// This is example code, replace with your own!

		// Text drawing

		canvas->Draw(application);
		c.Draw(application, Linal::Canvas::OFFSETX + 200, Linal::Canvas::OFFSETY + 200);

		//application->SetColor(Color(0, 0, 0, 255));
		//application->DrawText("Welcome to KMint", 400, 300);
		
		// Graph drawing
		/*application->SetColor(Color(0, 0, 0, 255));
		application->DrawLine(400, 350, 350, 400);
		application->DrawLine(350, 400, 450, 400);
		application->DrawLine(450, 400, 400, 350);

		application->SetColor(Color(0, 0, 255, 255));
		application->DrawCircle(400, 350, 10, true);
		application->DrawCircle(350, 400, 10, true);
		application->DrawCircle(450, 400, 10, true);*/

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}
