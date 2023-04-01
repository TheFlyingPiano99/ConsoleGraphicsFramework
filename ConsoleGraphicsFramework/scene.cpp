#include "scene.h"

cgf::Scene::~Scene() {
	for (auto actor : actors) {
		delete actor;
	}
}

void cgf::Scene::addActor(Actor* actor) {
	actors.push_back(actor);
}

/*
* Felhasználói bemenet kezelése
*/
void cgf::Scene::handleInput() {
	for (auto& actor : actors) {
		actor->handleInput(deltaT);
	}
}

/*
* Szereplők frissítése
*/
void cgf::Scene::update(AudioPlayer& player) {
	for (auto& actor : actors) {
		actor->update(deltaT, player, actors, toDelete, toAdd);
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
void cgf::Scene::draw(ConsoleRenderer& renderer) {
	std::sort(actors.begin(), actors.end(), [](Actor* a, Actor* b) { return a->getPos().z > b->getPos().z; });
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
