#pragma once
#include <iostream>
#include "States.h"

using namespace sf;
using namespace std;

class GameState;//Базовий клас 
class MenuState;// Клас стану гри

class Game {	//Основний клас гри
	RenderWindow window; //Вікно гри
	GameState* currentState; // Поточний стан гри
	//GameState* pendingState;
	Image icon; //Зображення іконки
public:
	//Налаштування вікна гри
	Game() : window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Windowed) {
		window.setFramerateLimit(60);//Обмеження 60 кадрів
		const filesystem::path path = "src/texture/icon.png";//Путь до іконки

		if (!icon.loadFromFile(path)) {
			cerr << "Помилка доступу до файлу: " << path << endl;
		}//Перевірка на завантаження іконки 
		window.setIcon(icon);//Встановлення іконки
		currentState = new MenuState(*this);// Початковий стан гри(меню)
		// pendingState = nullptr;
	}
	GameState* getState() { return currentState; }
	RenderWindow& getWindow() { return window; }
	//Головний цикл гри
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
	//зміна стану гри
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