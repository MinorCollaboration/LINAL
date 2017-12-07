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

	/******************************************
	 *             Scaling Matrix             *
	 ******************************************/

	// With Ints/doubles
	/* *
	auto a = Linal::GetScaleMatrix(1.2, 1.1);
	auto b = Linal::Matrix<double>{ 2, 4 };

	b.Set(1, 1, 3).Set(1, 2, 4).Set(1, 3, 6).Set(1, 4, 1);
	b.Set(2, 1, 2).Set(2, 2, 1).Set(2, 3, 7).Set(2, 4, 5);

	/* *
	auto c = a * b;
	/* */

	// With Points
	/* */
	auto square = Linal::Matrix<Linal::Point>{ 6 };
	auto topleft = Linal::Point(2, 6);
	auto topcenter = Linal::Point(4, 6);
	auto topright = Linal::Point(6, 6);
	auto bottomleft = Linal::Point(2, 2);
	auto bottomcenter = Linal::Point(4, 2);
	auto bottomright = Linal::Point(6, 2);

	square.Set(1, topleft);
	square.Set(2, topcenter);
	square.Set(3, topright);
	square.Set(4, bottomright);
	square.Set(5, bottomcenter);
	square.Set(6, bottomleft);

	/* *
	auto square = Linal::Matrix<double>{ 2,6 };
	square.Set(1, 1, 2).Set(1, 2, 4).Set(1, 3, 6).Set(1, 4, 2).Set(1, 5, 4).Set(1, 6, 6);
	square.Set(2, 1, 6).Set(2, 2, 6).Set(2, 3, 6).Set(2, 4, 2).Set(2, 5, 2).Set(2, 6, 2);
	/* */
	auto scale = Linal::GetScaleMatrix(1.759238, 1.236284);
	auto translate = Linal::GetTranslateMatrix(-2, -2);
	
	auto scaled = scale * square;
	//auto translated = translate * square;
	/* */

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

		scaled.Draw(application, Linal::OFFSETX, Linal::OFFSETY + Linal::HEIGHT);

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	delete application;
	return EXIT_SUCCESS;
}
