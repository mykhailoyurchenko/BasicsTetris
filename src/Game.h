#pragma once
#include <iostream>
#include "States.h"

using namespace sf;
using namespace std;

class GameState;
class MenuState;

class Game {
	RenderWindow window;
	GameState* currentState; 
	//GameState* pendingState;
	Image icon;
public:
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		window.setFramerateLimit(60);
		const filesystem::path path = "src/texture/icon.png";

		if (!icon.loadFromFile(path)) {
			cerr << "Помилка доступу до файлу: " << path << endl;
		}
		window.setIcon(icon);
		currentState = new MenuState(*this);
		// pendingState = nullptr;
	}
	GameState* getState() { return currentState; }
	RenderWindow& getWindow() { return window; }

	void run() {
		while (window.isOpen()) {
			currentState->update();
			while (optional event = window.pollEvent()) {
				currentState->eventHandler(*event);
			}
			currentState->draw(window);
			//applyPendingState();
		}
	}
	void setState(GameState* newState) {
		if (currentState) {
			delete currentState;
		}
		currentState = newState;
	}
	//void requestStateChange(GameState* newState) {
	//	if (pendingState) delete pendingState;
	//	pendingState = newState;
	//}
	//void applyPendingState() {
	//	if (pendingState) {
	//		setState(pendingState);
	//		pendingState = nullptr;
	//	}
	//}
};