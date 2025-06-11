#pragma once
#include "States.h"
#include <iostream>

using namespace std;

class GameState;//Базовий клас 
class MenuState;// Клас стану гри
enum class GameStateType { Menu, Play, Pause, Fail };

class Game { //Основний клас гри
	RenderWindow window; //Вікно гри
	Clock clock;
	unique_ptr<TetrisMenu> gameField;
	unique_ptr<GameState> currentState; // GameState* currentState; // Поточний стан гри
	Vector2f mousePos;//Позиція мишки
	Image icon; //Зображення іконки
public:
	//Налаштування вікна гри
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		mousePos = Vector2f(Mouse::getPosition(window)); //Обмеження 60 кадрів
		window.setFramerateLimit(60);
		//window.setKeyRepeatEnabled(false);
		const filesystem::path path = "src/texture/icon.png"; //Путь до іконки

		if (!icon.loadFromFile(path)) {
			cerr << "Помилка доступу до файлу: " << path << endl; //Перевірка на завантаження іконки 
		}
		window.setIcon(icon); //Встановлення іконки

		gameField = make_unique<TetrisMenu>(40, 750, 100);
		currentState = make_unique<MenuState>(*this);  // currentState = new MenuState(*this); // Початковий стан гри(меню)
	}
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	//weak_ptr<GameState> getState() { return currentState; }
	RenderWindow& getWindow() { return window; }
	Clock& getClock() { return clock; }
	Vector2f getMousePos() { return mousePos; }
	TetrisMenu& getField() { return *gameField; }

	void setState(GameStateType state) {
		switch (state) {
		case GameStateType::Menu:
			gameField = make_unique<TetrisMenu>(40, 750, 100);
			currentState = make_unique<MenuState>(*this);
			break;
		case GameStateType::Play:
			currentState = make_unique<PlayState>(*this);
			break;
		case GameStateType::Pause:
			currentState = make_unique<PauseState>(*this);
			break;
		case GameStateType::Fail:
			currentState = make_unique<GameOverState>(*this);
			break;
		}
	}
	//Головний цикл гри
	void run() {
		srand(time(0));
		while (window.isOpen()) {
			mousePos = Vector2f(Mouse::getPosition(window));
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