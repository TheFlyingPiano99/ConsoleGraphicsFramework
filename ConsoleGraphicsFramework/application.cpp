#include "application.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <cstdio>
#include <cmath>
#include <string>

#include "actor.h"

namespace cgf {
	void Application::buildScene()
	{
		for (int i = 0; i < 20; i++) {
			scene.addActor(new Grass());
		}

		for (int i = 0; i < 10; i++) {
			scene.addActor(new Flower());
		}

		Sky* sky = new Sky();
		scene.addActor(sky);

		Walkers* walkers = new Walkers();
		scene.addActor(walkers);

		Pole* pole = new Pole();
		scene.addActor(pole);

		Scoreboard* scoreboard = new Scoreboard();
		scene.addActor(scoreboard);
	}

	void Application::mainLoop()
	{
		// Time variables:
		clock_t currentTime = clock();
		clock_t prevTime = currentTime;
		scene.deltaT = 0.0f;
		float timeSinceLastDraw = 0.0f;
		const float drawInterval = 0.1f;

		srand(time(nullptr));		// Init random generation

		bool isRunning = true;

		while (isRunning)
		{
			// Measure delta time:
			currentTime = clock();
			clock_t difference = currentTime - prevTime;
			prevTime = currentTime;
			scene.deltaT = (float)difference / (float)CLOCKS_PER_SEC;

			scene.handleInput();

			scene.update();

			if (GetKeyState(VK_CANCEL) & 0x8000) {
				// TODO Not working
				isRunning = false;
			}

			timeSinceLastDraw += scene.deltaT;
			if (timeSinceLastDraw >= drawInterval) {
				scene.draw(renderer);
				timeSinceLastDraw = 0.0f;
			}
		}

	}

	void Application::run() {
		renderer.initRenderer(IVec2(150, 40));

		renderer.setColor(cgf::Color::foreground_bright_white);
		renderer.draw(L"   ________________ \n  |                |\n  | Oszlop kerülős |\n  |________________|\n\n");
		renderer.draw(L"   Irányítás:\n");
		renderer.draw(L"       [A] ... séta balra\n");
		renderer.draw(L"       [D] ... séta jobbra\n");
		renderer.draw("\n");
		renderer.draw("\n");
		renderer.draw(L"   A kezdéshez nyomj entert!\n");

		std::cin.get();	// Waiting for input
		renderer.clearScreen();

		buildScene();

		mainLoop();
	}

	Application::~Application()
	{
		renderer.clearScreen();
		renderer.reset();
	}
}

