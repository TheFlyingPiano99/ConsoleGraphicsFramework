#pragma once

#include <vector>

#include "vectorAlgebra.h"
#include "consoleRenderer.h"
#include "AudioPlayer.h"

using namespace VectorAlgebra;

namespace cgf {

	/*
	* Jelenetben résztvevő szereplők ősosztálya
	*/
	class Actor {
	public:

		Actor() {}

		virtual ~Actor() {}

		virtual void handleInput(float dt) {}

		virtual void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) {}

		virtual void clear(ConsoleRenderer& renderer) {}

		virtual void draw(ConsoleRenderer& renderer) {}

		Vec3 getPos() const {
			return pos;
		}

		void setPos(Vec3 _pos) {
			pos = _pos;
		}

		std::string_view getDescription() const {
			return description;
		}

		void setDescription(std::string_view _desc) {
			description = _desc;
		}

	protected:
		Vec3 pos;
		Vec3 prevPos;
		std::string description;
	};

	//-------------------------------------------------------


	/*
	* Égbolt
	*/
	class Sky : public Actor {
	public:
		Sky() : Actor() {
			pos = Vec3(0, 0, 10);
		}

		void draw(ConsoleRenderer& renderer) override;

	private:

	};

	/*
	* Járokelők
	*/
	class Walkers : public Actor {
	public:
		Walkers() {
			pos = Vec3(50, 38, -1);
			description = "walkers";
		}

		void handleInput(float dt) override;

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(ConsoleRenderer& renderer) override;

		void draw(ConsoleRenderer& renderer) override;

	private:
		float velocity = 0.0f;
		int animationPhase = 0;
		float animationTimer = 0.0f;
	};

	/*
	* Pózna
	*/
	class Pole : public Actor {
	public:
		Pole() : Actor() {
			pos = Vec3(20 + rand() % 100, 11, 1.0f);
			prevPos = pos;
			description = "pole";
		}

		~Pole();

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(cgf::ConsoleRenderer& renderer) override;

		void draw(cgf::ConsoleRenderer& renderer) override;

		bool isClaimed() const {
			return claimed;
		}

		void claim() {
			claimed = true;
		}

	private:
		bool claimed = false;
	};

	class Scoreboard : public Actor {
	public:
		Scoreboard() : Actor() {
			pos = Vec3(3, 2, -1);
			prevPos = pos;
			description = "scoreboard";
		}

		void clear(cgf::ConsoleRenderer& renderer) override;

		void draw(cgf::ConsoleRenderer& renderer) override;

		void IncrementScore(unsigned int increment) {
			score += increment;
		}

	private:
		unsigned int score = 0;

	};

	class Grass : public Actor {
	public:
		Grass() : Actor() {
			pos = Vec3(5.0f + rand() % 110, 12 + rand() % 10, 2.0f);
			prevPos = pos;
			description = "grass";
		}

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(ConsoleRenderer& renderer) override;

		void draw(ConsoleRenderer& renderer) override;

	private:
	};

	class Flower : public Actor {
	public:
		Flower() : Actor() {
			pos = Vec3(5.0f + rand() % 110, 12 + rand() % 10, 2.0f);
			prevPos = pos;
			description = "flower";
		}

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(ConsoleRenderer& renderer) override;

		void draw(ConsoleRenderer& renderer) override;

	private:
	};

	class Heart : public Actor {
	public:
		Heart(Vec3 _pos) : Actor() {
			velocity = Vec2((float)(rand() % 11) - 5.0f, -rand() % 5);
			pos = _pos + velocity * 2.0f - Vec3(0, 0, 3);
			prevPos = pos;
			description = "heart";
		}

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(ConsoleRenderer& renderer) override;

		void draw(ConsoleRenderer& renderer) override;

	private:
		Vec2 velocity;
		float lifeTime = 0.0f;
	};

	class Textbox : public Actor {
	public:
		Textbox(std::wstring_view _text) : Actor() {
			text = _text;
			pos = Vec3(60.0f, 8.0f, -1);
			prevPos = pos;
			description = "textbox";
		}

		void update(float dt, AudioPlayer& player, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) override;

		void clear(ConsoleRenderer& renderer) override;

		void draw(ConsoleRenderer& renderer) override;

	private:
		std::wstring text;
		float lifeTime = 0.0f;
		bool firstDraw = true;
	};
}
