#include "Game.h"

// Конструктор меню
MenuState::MenuState(Game& game) : GameState(game), playButtonText(font, "Play", 50), quitButtonText(font, "Quit", 40) {
	Vector2u winSize = game.getWindow().getSize();

	game.resetField();

	playButtonText.setPosition({winSize.x * 0.5f,winSize.y * 0.5f});

	quitButtonText.setPosition({ winSize.x * 0.498f, winSize.y * 0.57f});
}
// Обробка подій на клік
void MenuState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	Vector2f mousePos = game->getMousePos();

	if (playButtonText.isClicked(mousePos, event)) {
		game->setState<PlayState>();
	}
	else if (quitButtonText.isClicked(mousePos, event)) {
		game->getWindow().close();
	}
}
// Оновлення стану
void MenuState::update(const Time& delta) {
	GameState::update();
	Vector2f mousePos = game->getMousePos();

	playButtonText.update(mousePos);
	quitButtonText.update(mousePos);
}
// Відображення меню
void MenuState::draw(RenderWindow & window) {
	GameState::draw(window); // Відмальовка
	window.draw(playButtonText);
	window.draw(quitButtonText);
}