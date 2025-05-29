#include "Game.h"

PlayState::PlayState(Game& game) : GameState(game), backButton(Vector2f(150, 50)), 
backButtonText(font, "Go back", 50), scoreText(font, "0", 40) {
	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1740, 40));

	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));
}
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (backButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
		}
	}
}
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);
	window.draw(backButton);
	window.draw(backButtonText);
	window.draw(scoreText);
}
void PlayState::update() {
	GameState::update();

	if (backButton.getGlobalBounds().contains(game->getMousePos())) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(255, 255, 255, 255));
}