#include "actor.h"

#include "consoleRenderer.h"
#include <string>
#include <iostream>
#include "messages.h"


void Sky::draw(ConsoleRenderer& renderer) {
	renderer.setColor(Color::backgroundLightBlue);
	for (int x = 0; x <= 100; x += 50) {
		for (int y = 0; y < 10; y++) {
			if (renderer.setCursorPosition(x, y)) {
				std::cout << "                                                  ";	// String with spaces, do not delete space!
			}
		}
	}
	renderer.reset();
}

void Walkers::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) {
	animationTimer += dt;
	if (animationTimer > 1.0f) {
		animationTimer = 0.0f;
		animationPhase++;
		if (animationPhase >= 2) {
			animationPhase = 0;
		}
	}
	pos.x += velocity * dt;
	if (pos.x < 20.0f) {
		pos.x = 20.0f;
	}
	else if (pos.x > 130.0f) {
		pos.x = 130.0f;
	}

	for (auto actor : actors) {
		if (actor->getDescription() == "pole"
			&& distance(actor->getPos(), pos) < 5.0f && !static_cast<Pole*>(actor)->isClaimed()) {	// Hit pole
			static_cast<Pole*>(actor)->claim();
			toAdd.push_back(new Textbox(Messages::getRandomMessage()));
			auto messageIter = std::find_if(actors.begin(), actors.end(), [](Actor* const actor) -> bool { return actor->getDescription() == "textbox"; });
			if (messageIter != actors.end()) {
				toDelete.push_back(*messageIter);
			}
			auto iter = std::find_if(actors.begin(), actors.end(), [](Actor* const actor) -> bool { return actor->getDescription() == "scoreboard"; });
			for (int i = 0; i < 5; i++) {
				toAdd.push_back(new Heart(pos - Vec2(0, 12.0f)));
			}
			if (iter != actors.end()) {
				static_cast<Scoreboard*>(*iter)->IncrementScore(1);
			}
		}
	}
}

void Walkers::handleInput(float dt)
{
	if (GetKeyState('A') & 0x8000) {
		velocity -= dt * 30.0f;
	}
	if (GetKeyState('D') & 0x8000) {
		velocity += dt * 30.0f;
	}
	velocity *= expf(-dt * 1.5f);
}

void Walkers::clear(ConsoleRenderer& renderer)
{
	auto size = renderer.getSizeInChars();
	if (renderer.setCursorPosition((int)prevPos.x - 10, (int)prevPos.y - 16)) {
		std::cout << "   ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 11, (int)prevPos.y - 15)) {
		std::cout << "     ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 11, (int)prevPos.y - 14)) {
		std::cout << "     ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 11, (int)prevPos.y - 13)) {
		std::cout << "     ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 6, (int)prevPos.y - 13)) {
		std::cout << "  ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 12)) {
		std::cout << "      ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 5, (int)prevPos.y - 12)) {
		std::cout << "    ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 13, (int)prevPos.y - 11)) {
		std::cout << "        ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 4, (int)prevPos.y - 11)) {
		std::cout << "      ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 14, (int)prevPos.y - 10)) {
		std::cout << "          ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 3, (int)prevPos.y - 10)) {
		std::cout << "        ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 14, (int)prevPos.y - 9)) {
		std::cout << "          ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 2, (int)prevPos.y - 9)) {
		std::cout << "          ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 14, (int)prevPos.y - 8)) {
		std::cout << "          ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 1, (int)prevPos.y - 8)) {
		std::cout << "            ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 14, (int)prevPos.y - 7)) {
		std::cout << "           ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 2, (int)prevPos.y - 7)) {
		std::cout << "          ";
	}
	if (renderer.setCursorPosition((int)prevPos.x - 13, (int)prevPos.y - 6)) {
		std::cout << "           ";
	}
	if (renderer.setCursorPosition((int)prevPos.x + 1, (int)prevPos.y - 6)) {
		std::cout << "           ";
	}
	if (animationPhase == 0) {
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 5)) {	// Variant
			std::cout << "                        ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 4)) {
			std::cout << "                        ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 3)) {
			std::cout << "                       ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 2)) {
			std::cout << "                      ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 1)) {
			std::cout << "                     ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 12, (int)prevPos.y - 0)) {
			std::cout << "                     ";
		}
	}
	else {
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 5)) {	// Variant
			std::cout << "                           ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 4)) {
			std::cout << "                           ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 3)) {
			std::cout << "                          ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 2)) {
			std::cout << "                         ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 1)) {
			std::cout << "                        ";
		}
		if (renderer.setCursorPosition((int)prevPos.x - 15, (int)prevPos.y - 0)) {
			std::cout << "                        ";
		}
	}
}

void Walkers::draw(ConsoleRenderer& renderer) {
	if (IVec2(pos) != IVec2(prevPos)) {
		clear(renderer);
	}

	renderer.setColor(Color::foregroundLightYellow);
	if (renderer.setCursorPosition((int)pos.x - 10, (int)pos.y - 16)) {
		std::cout << "___";
	}
	if (renderer.setCursorPosition((int)pos.x - 11, (int)pos.y - 15)) {
		std::cout << "/   \\";
	}
	if (renderer.setCursorPosition((int)pos.x - 11, (int)pos.y - 14)) {
		std::cout << "\\   /";
	}
	if (renderer.setCursorPosition((int)pos.x - 11, (int)pos.y - 13)) {
		std::cout << "\\   /";
	}
	if (renderer.setCursorPosition((int)pos.x + 6, (int)pos.y - 13)) {
		std::cout << "__";
	}
	if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 12)) {
		std::cout << "__| |_";
	}
	if (renderer.setCursorPosition((int)pos.x + 5, (int)pos.y - 12)) {
		std::cout << "/  \\";
	}
	if (renderer.setCursorPosition((int)pos.x - 13, (int)pos.y - 11)) {
		std::cout << "/      \\";
	}
	if (renderer.setCursorPosition((int)pos.x + 4, (int)pos.y - 11)) {
		std::cout << "/||||\\";
	}
	if (renderer.setCursorPosition((int)pos.x - 14, (int)pos.y - 10)) {
		std::cout << "|        |";
	}
	if (renderer.setCursorPosition((int)pos.x + 3, (int)pos.y - 10)) {
		std::cout << "_||||||_";
	}
	if (renderer.setCursorPosition((int)pos.x - 14, (int)pos.y - 9)) {
		std::cout << "| |    | |";
	}
	if (renderer.setCursorPosition((int)pos.x + 2, (int)pos.y - 9)) {
		std::cout << "/ \\||||/ \\";
	}
	if (renderer.setCursorPosition((int)pos.x - 14, (int)pos.y - 8)) {
		std::cout << "| |    | |";
	}
	if (renderer.setCursorPosition((int)pos.x + 1, (int)pos.y - 8)) {
		std::cout << "| | \\||/ | |";
	}
	if (renderer.setCursorPosition((int)pos.x - 14, (int)pos.y - 7)) {
		std::cout << "| |    |\\ \\";
	}
	if (renderer.setCursorPosition((int)pos.x + 2, (int)pos.y - 7)) {
		std::cout << "||      ||";
	}
	if (renderer.setCursorPosition((int)pos.x - 13, (int)pos.y - 6)) {
		std::cout << "\\|____|  \\\\";
	}
	if (renderer.setCursorPosition((int)pos.x + 1, (int)pos.y - 6)) {
		std::cout << "//|      ||";
	}
	if (animationPhase == 0) {
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 5)) {	// Variant
			std::cout << "| |  |   \\\\ // /      \\|";
		}
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 4)) {
			std::cout << "| |  |    \\~/  |~~~~~~|/";
		}
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 3)) {
			std::cout << "| |  |         |   |  |";
		}
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 2)) {
			std::cout << "| |  |          \\  | /";
		}
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 1)) {
			std::cout << "| |  |           | ||";
		}
		if (renderer.setCursorPosition((int)pos.x - 12, (int)pos.y - 0)) {
			std::cout << "| | /            | ||";
		}
	}
	else {
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 5)) {	// Variant
			std::cout << "   |  | |   \\\\ // /      \\|";
		}
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 4)) {
			std::cout << "   |  | |    \\~/  |~~~~~~|/";
		}
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 3)) {
			std::cout << "   |  | |         |  |   |";
		}
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 2)) {
			std::cout << "   |  | |          \\ |  /";
		}
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 1)) {
			std::cout << "   |  | |           || |";
		}
		if (renderer.setCursorPosition((int)pos.x - 15, (int)pos.y - 0)) {
			std::cout << "    \\ | |           || |";
		}
	}
	prevPos = pos;
	renderer.reset();
}

Pole::~Pole() {
}

void Pole::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) {
	pos += dt * Vec2(0, 0.2f) * fmaxf(pos.y, 0.0f);
	if (pos.y >= 40.0f) {
		toDelete.push_back(this);

		
		// Create next pole:
		auto nextPole = new Pole();
		toAdd.push_back(nextPole);
		
	}
}

void Pole::clear(ConsoleRenderer& renderer)
{
	int size = (int)fmaxf(100.0f / (50 - prevPos.y), 0.0f);
	for (int i = 0; i < size; i++) {
		if (prevPos.y - size + i > 0) {
			if (renderer.setCursorPosition(prevPos.x - 2, prevPos.y - size + i)) {
				std::cout << "     ";
			}
		}
	}
	renderer.reset();
}

void Pole::draw(ConsoleRenderer& renderer) {
	if (IVec2(pos) != IVec2(prevPos)) {
		clear(renderer);
	}
	
	int size = (int)fmaxf(100.0f / (50 - pos.y), 0.0f);
	for (int i = 0; i < size; i++) {
		if (pos.y - size + i > 0) {
			if (renderer.setCursorPosition(pos.x - 2, pos.y - size + i)) {
				if ((i > 0 && i < size - 1) || size == 2 && i > 0) {
					if (size <= 2) {
						std::cout << "  |  ";
					}
					else if (size <= 5) {
						std::cout << "  || ";
					}
					else if (size <= 10) {
						std::cout << " | | ";
					}
				}
				else if (i == 0) {
					if (size <= 2) {
						std::cout << "  T  ";
					}
					else if (size <= 5) {
						std::cout << "  () ";
					}
					else if (size <= 10) {
						std::cout << " (_) ";
					}
				}
				else if (i == size - 1) {
					if (size <= 5) {
						std::cout << "  || ";
					}
					else if (size <= 10) {
						std::cout << " |_| ";
					}
				}
			}
		}
	}
	
	prevPos = pos;
	renderer.reset();
}

void Scoreboard::clear(ConsoleRenderer& renderer)
{
	renderer.setCursorPosition(prevPos.x, prevPos.y);
	std::cout << "          ";
}

void Scoreboard::draw(ConsoleRenderer& renderer)
{
	clear(renderer);
	renderer.setCursorPosition(prevPos.x, prevPos.y);
	renderer.draw(std::wstring(L"Megkerült oszlopok: ").append(std::to_wstring(score)));
	renderer.reset();
}

void Grass::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd)
{
	pos += dt * Vec2(0, 0.2f) * fmaxf(pos.y, 0.0f);
	if (pos.y >= 40) {
		toDelete.push_back(this);
		toAdd.push_back(new Grass());
	}
}

void Grass::clear(ConsoleRenderer& renderer)
{
	renderer.setCursorPosition(prevPos.x, prevPos.y);
	std::cout << "   ";
}

void Grass::draw(ConsoleRenderer& renderer)
{
	clear(renderer);
	renderer.setCursorPosition(pos.x, pos.y);
	renderer.setColor(Color::foregroundLightGreen);
	if (pos.y < 20.0f) {
		std::cout << " ~ ";
	}
	else if (pos.y < 30.0f) {
		std::cout << " V ";
	}
	else {
		std::cout << "\\V/";
	}
	renderer.reset();
	prevPos = pos;
}


void Flower::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd)
{
	pos += dt * Vec2(0, 0.2f) * fmaxf(pos.y, 0.0f);
	if (pos.y >= 40) {
		toDelete.push_back(this);
		toAdd.push_back(new Flower());
	}
}

void Flower::clear(ConsoleRenderer& renderer)
{
	renderer.setCursorPosition(prevPos.x, prevPos.y - 1);
	std::cout << " ";
	renderer.setCursorPosition(prevPos.x, prevPos.y - 0);
	std::cout << " ";
}

void Flower::draw(ConsoleRenderer& renderer)
{
	clear(renderer);
	if (pos.y < 30.0f) {
		renderer.setColor(Color::foregroundLightYellow);
		renderer.setCursorPosition(pos.x, pos.y - 0);
		std::cout << "*";
	}
	else {
		renderer.setCursorPosition(pos.x, pos.y - 1);
		renderer.setColor(Color::foregroundLightYellow);
		std::cout << "*";
		renderer.setColor(Color::foregroundGreen);
		renderer.setCursorPosition(pos.x, pos.y - 0);
		std::cout << "|";
	}
	renderer.reset();
	prevPos = pos;
}


void Heart::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd)
{
	pos += dt * velocity;
	lifeTime += dt;
	if (lifeTime > 2.0f) {
		toDelete.push_back(this);
	}
}

void Heart::clear(ConsoleRenderer& renderer)
{
	renderer.setCursorPosition(prevPos.x - 2, prevPos.y - 2);
	std::cout << "     ";
	renderer.setCursorPosition(prevPos.x - 2, prevPos.y - 1);
	std::cout << "     ";
	renderer.setCursorPosition(prevPos.x - 2, prevPos.y - 0);
	std::cout << "     ";
	renderer.setCursorPosition(prevPos.x - 2, prevPos.y + 1);
	std::cout << "     ";
}

void Heart::draw(ConsoleRenderer& renderer)
{
	clear(renderer);
	renderer.setColor(Color::foregroundLightPurple);
	renderer.setCursorPosition(pos.x - 2, pos.y - 2);
	std::cout << " _ _ ";
	renderer.setCursorPosition(pos.x - 2, pos.y - 1);
	std::cout << "( V )";
	renderer.setCursorPosition(pos.x - 2, pos.y - 0);
	std::cout << " \\ / ";
	renderer.setCursorPosition(pos.x - 2, pos.y + 1);
	std::cout << "  V  ";
	prevPos = pos;
	renderer.reset();
}

void Textbox::update(float dt, const std::vector<Actor*>& actors, std::vector<Actor*>& toDelete, std::vector<Actor*>& toAdd) {
	lifeTime += dt;
	if (lifeTime > 8.0f) {
		toDelete.push_back(this);
	}
}

void Textbox::clear(ConsoleRenderer& renderer)
{
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < text.size() + 4; x++) {
			renderer.setCursorPosition(prevPos.x + x - text.size() / 2, prevPos.y - y);
			std::cout << " ";
		}
	}
}

void Textbox::draw(ConsoleRenderer& renderer)
{
	if (firstDraw || IVec2(pos) != IVec2(prevPos)) {
		firstDraw = false;
		clear(renderer);
	}
	int minMargin = 2;
	int timesTen = (text.size() + 2.0f * minMargin + 2.0f) / 10.0f + 1;
	int posOffset = timesTen * 10 / 2.0;
	int margin = (timesTen * 10 - text.size()) / 2.0f;
	renderer.setColor(Color::foregroundBrightWhite);
	for (int x = 0; x < timesTen; x++) {
		renderer.setCursorPosition(pos.x - posOffset + x * 10, pos.y - 4);
		std::cout << "**********";
	}
	for (int x = 0; x < timesTen; x++) {
		renderer.setCursorPosition(pos.x - posOffset + x * 10, pos.y - 3);
		std::cout << "          ";
	}
	for (int x = 0; x < timesTen; x++) {
		renderer.setCursorPosition(pos.x - posOffset + x * 10, pos.y - 2);
		std::cout << "          ";
	}
	for (int x = 0; x < timesTen; x++) {
		renderer.setCursorPosition(pos.x - posOffset + x * 10, pos.y - 1);
		std::cout << "          ";
	}
	for (int x = 0; x < timesTen; x++) {
		renderer.setCursorPosition(pos.x - posOffset + x * 10, pos.y - 0);
		std::cout << "**********";
	}
	renderer.draw(pos.x - posOffset, pos.y - 3, "*");
	renderer.draw(pos.x - posOffset, pos.y - 2, "* ");
	renderer.draw(pos.x - posOffset, pos.y - 1, "*");
	renderer.draw(pos.x - posOffset + margin, pos.y - 2, text);
	renderer.draw(pos.x - posOffset + timesTen * 10 - 1, pos.y - 3, "*");
	renderer.draw(pos.x - posOffset + timesTen * 10 - 2, pos.y - 2, " *");
	renderer.draw(pos.x - posOffset + timesTen * 10 - 1, pos.y - 1, "*");

	prevPos = pos;
	renderer.reset();
}