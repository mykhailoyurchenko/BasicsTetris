#include <States.h>
#include <iostream>

using namespace std;
//Конструктор 
GameState::GameState(Game& game) : tetrisText(tetrisFont, "Tetris", 70), background(backgroundTexture) {
	//Пути к файлам
	const filesystem::path path1 = "src/texture/background.jpg";
	const filesystem::path path2 = "src/fonts/Roboto_Condensed-Black.ttf";
	const filesystem::path path3 = "src/fonts/Oi-Regular.ttf";
	//Загрузка текстур,шрифта
	if (!backgroundTexture.loadFromFile(path1)) cerr << "Помилка доступу до файлу: " << path1 << endl;
	if (!font.openFromFile(path2)) cerr << "Помилка доступу до файлу: " << path2 << endl;
	if (!tetrisFont.openFromFile(path3)) cerr << "Помилка доступу до файлу: " << path3 << endl;

	//Настройка текста
	tetrisText.setFillColor(Color::White);
	tetrisText.setPosition(Vector2f(200, 500));
	background.setTexture(backgroundTexture);
}

void GameState::draw(RenderWindow& window) {
	window.draw(background);//Отрисовка background
}