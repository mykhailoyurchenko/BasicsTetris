#include "Game.h"

// Конструктор меню
MenuState::MenuState(Game& game) : GameState(game), playButtonText(font, "Play", 50), quitButtonText(font, "Quit", 40) {
	Vector2u winSize = game.getWindow().getSize();
	centerAll(playButtonText, quitButtonText);

	game.setField(make_unique<TetrisMenu>(40, 750, 100, winSize));

	playButtonText.setFillColor(Color::White);
	playButtonText.setPosition({winSize.x * 0.5f,winSize.y * 0.5f});

	quitButtonText.setFillColor(Color::White);
	quitButtonText.setPosition({winSize.x * 0.498f, winSize.y * 0.57f});
}
// Обробка подій на клік
void MenuState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) { // Перевірка натискання миші
		if (playButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PlayState>();
			return;
		}
		if (quitButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->getWindow().close();
		}
	}
}
// Оновлення стану
void MenuState::update(const Time& delta) {
	GameState::update();
	if (quitButtonText.getGlobalBounds().contains(game->getMousePos())) {
		quitButtonText.setFillColor(Color::Yellow);
	}
	else {
		quitButtonText.setFillColor(Color::White);
	}
	// Зміна кольору тексту 
	if (playButtonText.getGlobalBounds().contains(game->getMousePos())) {
		playButtonText.setFillColor(Color::Yellow);
	}
	else playButtonText.setFillColor(Color::White);
}
// Відображення меню
void MenuState::draw(RenderWindow & window) {
	GameState::draw(window); // Відмальовка
	window.draw(playButtonText);
	window.draw(quitButtonText);
}