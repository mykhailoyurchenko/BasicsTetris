#pragma once
#include "States.h"
#include <iostream>

using namespace std;

class GameState;//Базовий клас 
class MenuState;// Клас стану гри

class Game { //Основний клас гри
	RenderWindow window; //Вікно гри
	Clock clock;
	unique_ptr<TetrisMenu> gameField;
	unique_ptr<GameState> currentState; // GameState* currentState; // Поточний стан гри
	Vector2f mousePos;//Позиція мишки
	Vector2u winSize; //Розмір вікна
	Image icon; //Зображення іконки
public:
	//Налаштування вікна гри
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Fullscreen) {
		mousePos = Vector2f(Mouse::getPosition(window));
		window.setFramerateLimit(60); //Обмеження 60 кадрів

		const filesystem::path path = "src/texture/icon.png"; //Путь до іконки

		if (!icon.loadFromFile(path)) {
			cerr << "File access error: " << path << endl; //Перевірка на завантаження іконки 
		}
		window.setIcon(icon); //Встановлення іконки

		currentState = make_unique<MenuState>(*this);  // currentState = new MenuState(*this); // Початковий стан гри(меню)
	}
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	RenderWindow& getWindow() { return window; }
	Clock& getClock() { return clock; }
	Vector2f getMousePos() { return mousePos; }
	TetrisMenu& getField() { return *gameField; }

	void setField(unique_ptr<TetrisMenu> field) {
		gameField = move(field);
	}
	template <typename State> void setState() {
		static_assert(is_base_of_v<GameState, State>,
			"State must inherit from BaseState");
		currentState = make_unique<State>(*this);
	}
	//Головний цикл гри
	void run() {
		srand(time(0));
		while (window.isOpen()) {
			mousePos = Vector2f(Mouse::getPosition(window));
			winSize = window.getSize();
			currentState->update(clock.restart());
			while (optional event = window.pollEvent()) {
				currentState->eventHandler(*event);
			}
			window.clear();
			currentState->draw(window);
			window.display();
		}
	}
};