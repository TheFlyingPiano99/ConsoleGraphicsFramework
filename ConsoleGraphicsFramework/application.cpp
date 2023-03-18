#include "application.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <cstdio>
#include <cmath>
#include <string>

#include "scene.h"
#include "actor.h"
#include "consoleRenderer.h"

void Application::run() const {
	ConsoleRenderer renderer;
	renderer.initRenderer(IVec2(150, 40));

	//renderer.setColor(foregroundBRIGHT_WHITE);
	renderer.draw(L"   ________________ \n  |                |\n  | Oszlop kerülős |\n  |________________|\n\n");
	renderer.draw(L"   Irányítás:\n");
	renderer.draw(L"       [A] ... séta balra\n");
	renderer.draw(L"       [D] ... séta jobbra\n");
	renderer.draw("\n");
	renderer.draw("\n");
	renderer.draw(L"   A kezdéshez nyomj entert!\n");
	getchar();	// Varakozas inputra
	renderer.clearScreen();

	Scene scene;

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

	// Time variables:
	clock_t currentTime = clock();
	clock_t prevTime = currentTime;
	scene.deltaT = 0.0f;
	float timeSinceLastDraw = 0.0f;
	const float drawInterval = 0.1f;

	srand(time(NULL));		// Init random generation
	
	bool isRunning = TRUE;

	while (isRunning)
	{
		// Measure delta time:
		currentTime = clock();
		clock_t difference = currentTime - prevTime;
		prevTime = currentTime;
		scene.deltaT = (float)difference / (float)CLOCKS_PER_SEC;

		scene.handleInput();

		scene.update();

		timeSinceLastDraw += scene.deltaT;
		if (timeSinceLastDraw >= drawInterval) {
			scene.draw(renderer);
			timeSinceLastDraw = 0.0f;
		}
	}
	std::cout << "Vege\n";

}