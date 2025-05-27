#pragma once
#include <iostream>
#include <States.h>

class Game {
	RenderWindow window;
	GameState* currentState;
	Image icon;
public:
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Fullscreen) {
		window.setFramerateLimit(60);
		const std::filesystem::path path = "src/texture/icon.png";

		if (!icon.loadFromFile(path)) {
			std::cerr << "Помилка доступу до файлу: " << path << std::endl;
		}
		window.setIcon(icon);
		currentState = new MenuState(*this);
	}
	GameState getState() { return *currentState; }
	RenderWindow& getWindow() { return window; }
	void setState(GameState* newState) {
		if (currentState) {
			delete currentState;
		}
		currentState = newState;
	}
};