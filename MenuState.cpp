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
		if (playButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PlayState>();
		}
	}
}
// Оновлення стану
void MenuState::update() {
	GameState::update();
	// Зміна кольору тексту 
	if (playButton.getGlobalBounds().contains(game->getMousePos())) {
		playButtonText.setFillColor(Color::Yellow);
	}
	else playButtonText.setFillColor(Color::White);
}
// Відображення меню
void MenuState::draw(RenderWindow& window) {
	GameState::draw(window); // Відмальовка
	window.draw(playButton);
	window.draw(playButtonText);
}	