#pragma once

#include <vector>
#include <algorithm>

#include "actor.h"

namespace cgf {
	class Scene {
	public:
		float deltaT = 0.0f;	// sec

		Scene() {

		}

		~Scene();

		void addActor(Actor* actor);

		/*
		* Felhasználói bemenet kezelése
		*/
		void handleInput();

		/*
		* Szereplők frissítése
		*/
		void update();

		/*
		* Kirajzolás
		*/
		void draw(ConsoleRenderer& renderer);

	private:
		std::vector<Actor*> actors;
		std::vector<Actor*> toDelete;
		std::vector<Actor*> toAdd;
		std::vector<Actor*> toClear;
	};
}
