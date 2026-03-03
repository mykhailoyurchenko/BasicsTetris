#pragma once
#include "States.h"
#include "AssetManager.h"
#include <iostream>

using namespace std;

class Game { //Основний клас гри
	RenderWindow window; //Вікно гри
	Clock clock;
	AssetManager assets;
	optional<TetrisEngine> gameField;
	unique_ptr<GameState> currentState; // GameState* currentState; // Поточний стан гри
	Vector2i mousePos;//Позиція мишки
	Vector2u winSize = { 1920, 1080 }; //Розмір вікна
	Image icon; //Зображення іконки
public:
	//Налаштування вікна гри
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		mousePos = Mouse::getPosition(window);
		window.setFramerateLimit(60); //Обмеження 60 кадрів

		const filesystem::path path = filesystem::current_path() / "src" / "texture" / "icon.png";//"src/texture/icon.png";

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
	Vector2f getMousePos() { return Vector2f(mousePos); }
	TetrisEngine& getField() { return *gameField; }
	AssetManager& getAssets() { return assets; }

	void resetField() {
		gameField.emplace(winSize);
	}
	template <typename State> void setState() {
		static_assert(is_base_of_v<GameState, State>,
			"State must inherit from GameState");
		currentState = make_unique<State>(*this);
	}
	//Головний цикл гри
	void run() {
		srand(time(0));
		while (window.isOpen()) {
			mousePos = Mouse::getPosition(window);
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