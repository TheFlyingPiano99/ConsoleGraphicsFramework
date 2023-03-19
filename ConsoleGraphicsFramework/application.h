#pragma once

#include "scene.h"
#include "consoleRenderer.h"

class Application {
public:
	~Application();

	void run();

private:
	void buildScene();
	void mainLoop();

	Scene scene;
	ConsoleRenderer renderer;
};