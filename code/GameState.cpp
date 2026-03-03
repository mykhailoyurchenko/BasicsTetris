#include "Game.h"

//Конструктор 
GameState::GameState(Game& game) : game(&game), 
	font(game.getAssets().getFont("src/fonts/Roboto_Condensed-Black.ttf")),
	tetrisFont(game.getAssets().getFont("src/fonts/Oi-Regular.ttf")),
	backgroundSprite(game.getAssets().getTexture("src/texture/background.jpg")),
	tetrisText(tetrisFont, "Tetris", 70) 
{
	Vector2u winSize = game.getWindow().getSize();
	//Настройка тексту
	tetrisText.setPosition(Vector2f(winSize.x * 0.1f, winSize.y * 0.46f)); // Змінити на вілносні координати
}
void GameState::eventHandler(Event& event) {
	if (event.is<Event::Closed>()) {
		game->getWindow().close();
	}
}
void GameState::draw(RenderWindow& window) {
	window.draw(backgroundSprite);  //рендер background
	window.draw(tetrisText);
}