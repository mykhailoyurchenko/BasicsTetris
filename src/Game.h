#pragma once
#include "States.h"
#include <iostream>

using namespace sf;
using namespace std;

class GameState;
class MenuState;

class Game {
	RenderWindow window;
	shared_ptr<GameState> currentState; // GameState* currentState;
	Vector2f mousePos;//Позиція мишки
	Image icon;
public:
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		mousePos = Vector2f(Mouse::getPosition(window));
		window.setFramerateLimit(60);
		const filesystem::path path = "src/texture/icon.png";

		if (!icon.loadFromFile(path)) {
			cerr << "Помилка доступу до файлу: " << path << endl;
		}
		window.setIcon(icon);
		currentState = make_shared<MenuState>(*this);  // currentState = new MenuState(*this);
	}
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	weak_ptr<GameState> getState() { return currentState; }
	RenderWindow& getWindow() { return window; }
	Vector2f getMousePos() { return mousePos; }
	template<typename State>
	void setState() {
		currentState = make_shared<State>(*this); //currentState = newState
	}
	void run() {
		while (window.isOpen()) {
			mousePos = Vector2f(Mouse::getPosition(window));
			currentState->update();
			while (optional event = window.pollEvent()) {
				currentState->eventHandler(*event);
			}
			window.clear();
			currentState->draw(window);
			window.display();
		}
	}

};