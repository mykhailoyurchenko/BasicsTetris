#include "Game.h"

// Конструктор меню
MenuState::MenuState(Game& game) : GameState(game), playButton(Vector2f(150, 50)), playButtonText(font, "Play", 50), quitButton(Vector2f(150, 50)), quitButtonText(font, "Quit", 40) {
	playButton.setFillColor(Color(0, 0, 0, 0.0));
	playButton.setPosition(Vector2f(850, 500));

	playButtonText.setFillColor(Color::White);
	playButtonText.setPosition(Vector2f(900, 490));

	quitButton.setFillColor(Color(0, 0, 0, 0.0));
	quitButton.setPosition(Vector2f(1750, 200));

	quitButtonText.setFillColor(Color::White);
	quitButtonText.setPosition(Vector2f(1750, 200));
}
// Обробка подій на клік
void MenuState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) { // Перевірка натискання миші
		if (playButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PlayState>();
			return;
		}
		if (quitButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->getWindow().close();
		}
	}
}
// Оновлення стану
void MenuState::update() {
	GameState::update();
	if (quitButton.getGlobalBounds().contains(game->getMousePos())) {
		quitButtonText.setFillColor(Color::Yellow);
	}
	else {
		quitButtonText.setFillColor(Color::White);
	}
	// Зміна кольору тексту 
	if (playButton.getGlobalBounds().contains(game->getMousePos())) {
		playButtonText.setFillColor(Color::Yellow);
	}
	else playButtonText.setFillColor(Color::White);
}
// Відображення меню
	void MenuState::draw(RenderWindow & window) {
	GameState::draw(window); // Відмальовка
	window.draw(playButton);
	window.draw(playButtonText);
	window.draw(quitButton);
	window.draw(quitButtonText);
}	