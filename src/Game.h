#pragma once
#include "States.h"
#include <iostream>

using namespace sf;
using namespace std;

class GameState;//Базовий клас 
class MenuState;// Клас стану гри
enum class GameStateType { Menu, Play, Pause };

class Game { //Основний клас гри
	RenderWindow window; //Вікно гри
	Clock clock;
	unique_ptr<gridType> grid;
	shared_ptr<GameState> currentState; // GameState* currentState; // Поточний стан гри
	Vector2f mousePos;//Позиція мишки
	Image icon; //Зображення іконки
public:
	//Налаштування вікна гри
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		mousePos = Vector2f(Mouse::getPosition(window)); //Обмеження 60 кадрів
		window.setFramerateLimit(60);
		const filesystem::path path = "src/texture/icon.png"; //Путь до іконки

		if (!icon.loadFromFile(path)) {
			cerr << "Помилка доступу до файлу: " << path << endl; //Перевірка на завантаження іконки 
		}
		window.setIcon(icon); //Встановлення іконки

		currentState = make_shared<MenuState>(*this);  // currentState = new MenuState(*this); // Початковий стан гри(меню)
		grid = make_unique<gridType>();
	}
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	//зміна стану гри
	weak_ptr<GameState> getState() { return currentState; }
	RenderWindow& getWindow() { return window; }
	Clock& getClock() { return clock; }
	Vector2f getMousePos() { return mousePos; }
	gridType& getGrid() { return *grid; }

	void initializeGrid() {
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 20; y++) {
				(*grid)[x][y].x = x;
				(*grid)[x][y].y = y;
				(*grid)[x][y].color = Color::Black;
				(*grid)[x][y].isFull = false;
			}
		}
	}
	void setState(GameStateType state) {
		switch (state) {
		case GameStateType::Menu:
			currentState = make_shared<MenuState>(*this);
			initializeGrid();
			break;
		case GameStateType::Play:
			currentState = make_shared<PlayState>(*this);
			//grid = currentState->getGrid();
			break;
		case GameStateType::Pause:
			currentState = make_shared<PauseState>(*this);
			//grid = currentState->getGrid();
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