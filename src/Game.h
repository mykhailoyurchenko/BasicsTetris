#pragma once
#include "States.h"
#include <iostream>

using namespace sf;
using namespace std;

class GameState;//Базовий клас 
class MenuState;// Клас стану гри


class Game { //Основний клас гри
	RenderWindow window; //Вікно гри
	shared_ptr<std::vector<std::vector<CellData>>> grid;
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
		
	}
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	//зміна стану гри
	weak_ptr<GameState> getState() { return currentState; }
	RenderWindow& getWindow() { return window; }
	Vector2f getMousePos() { return mousePos; }
	template<typename State>
	void setState() {
		currentState = make_shared<State>(*this); //currentState = newState
		
	}
	//Головний цикл гри
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