#include "Game.h"

// Конструктор меню
MenuState::MenuState(Game& game) : GameState(game), playButton(Vector2f(150, 50)), playButtonText(font, "Play", 50) {
	playButton.setFillColor(Color(0, 0, 0, 0.0));
	playButton.setPosition(Vector2f(850, 500));

	playButtonText.setFillColor(Color::White);
	playButtonText.setPosition(Vector2f(900, 490));
}
// Обробка подій на клік
void MenuState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) { // Перевірка натискання миші

		Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
		if (playButton.getGlobalBounds().contains(mousePos)) {
			game->setState(new PlayState(*game));
		}
	}
}
// Оновлення стану
void MenuState::update() {
	Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
	// Зміна кольору тексту 
	if (playButton.getGlobalBounds().contains(mousePos)) {
		playButtonText.setFillColor(Color::Yellow);
	}
	else playButtonText.setFillColor(Color::White);
}
// Відображення меню
void MenuState::draw(RenderWindow& window) {
	GameState::draw(window); // Відмальовка
	window.draw(playButton);
	window.draw(playButtonText);
	window.display();
}	