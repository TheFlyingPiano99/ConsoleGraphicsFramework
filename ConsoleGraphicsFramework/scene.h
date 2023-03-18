#pragma once

#include <vector>
#include <algorithm>

#include "actor.h"


class Scene {
public:
	float deltaT = 0.0f;

	Scene() {

	}

	~Scene() {
		for (auto actor : actors) {
			delete actor;
		}
	}

	void addActor(Actor* actor) {
		actors.push_back(actor);
	}

	/*
	* Felhasználói bemenet kezelése
	*/
	void handleInput() {
		for (auto& actor : actors) {
			actor->handleInput(deltaT);
		}
	}

	/*
	* Szereplők frissítése
	*/
	void update() {
		for (auto& actor : actors) {
			actor->update(deltaT, actors, toDelete, toAdd);
		}
		// Clear and delete objects:
		for (auto actor : toDelete) {
			auto iter = std::find(actors.begin(), actors.end(), actor);
			if (iter != actors.end()) {
				actors.erase(iter);
				toClear.push_back(actor);
			}
		}
		toDelete.clear();
		for (auto actor : toAdd) {
			actors.push_back(actor);
		}
		toAdd.clear();
	}

	/*
	* Kirajzolás
	*/
	void draw(ConsoleRenderer& renderer) {
		std::sort(actors.begin(), actors.end(), [](Actor* a, Actor* b) { return a->getPos().y < b->getPos().y; });
		for (auto& actor : actors) {
			actor->draw(renderer);
		}

		// Clear and delete objects:
		for (auto actor : toClear) {
			actor->clear(renderer);
			delete actor;
		}
		toClear.clear();
	}

private:
	std::vector<Actor*> actors;
	std::vector<Actor*> toDelete;
	std::vector<Actor*> toAdd;
	std::vector<Actor*> toClear;
};
