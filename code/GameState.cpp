#include "Game.h"
#include <iostream>

//Конструктор 
GameState::GameState(Game& game) : game(&game), tetrisText(tetrisFont, "Tetris", 70) {
	using namespace filesystem;
	//Пути к файлам
	const path path1 = "src/texture/background.jpg";
	const path path2 = "src/fonts/Roboto_Condensed-Black.ttf";
	const path path3 = "src/fonts/Oi-Regular.ttf";
	
	//Загрузка текстур,шрифта
	if (!backgroundTexture.loadFromFile(path1)) cerr << "Помилка доступу до файлу: " << path1 << endl;
	if (!font.openFromFile(path2)) cerr << "Помилка доступу до файлу: " << path2 << endl;
	if (!tetrisFont.openFromFile(path3)) cerr << "Помилка доступу до файлу: " << path3 << endl;
	backgroundSprite = new Sprite(backgroundTexture);

	//Настройка тексту
	tetrisText.setFillColor(Color::White);
	tetrisText.setPosition(Vector2f(200, 500)); // Змінити на вілносні координати
}
void GameState::eventHandler(Event& event) {
	if (event.is<Event::Closed>()) {
		game->getWindow().close();
	}
}
void GameState::draw(RenderWindow& window) {
	window.draw(*backgroundSprite);  //рендер background
	window.draw(tetrisText);
}