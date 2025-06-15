#include "Game.h"

//Конструктор 
GameState::GameState(Game& game) : game(&game), tetrisText(tetrisFont, "Tetris", 70) {
	using namespace filesystem;
	//Пути к файлам
	const path path1 = "src/texture/background.jpg";
	const path path2 = "src/fonts/Roboto_Condensed-Black.ttf";
	const path path3 = "src/fonts/Oi-Regular.ttf";
	
	//Загрузка текстур,шрифта
	if (!backgroundTexture.loadFromFile(path1)) cerr << "File access error: " << path1 << endl;
	if (!font.openFromFile(path2)) cerr << "File access error: " << path2 << endl;
	if (!tetrisFont.openFromFile(path3)) cerr << "File access error: " << path3 << endl;
	backgroundSprite = std::make_unique<Sprite>(backgroundTexture);

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