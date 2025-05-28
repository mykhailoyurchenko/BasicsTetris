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
		Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
		if (backButton.getGlobalBounds().contains(mousePos)) {
			game->setState(new PlayState(*game));
		}
	}
}
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);
	window.draw(backButton);
	window.draw(backButtonText);
	window.draw(scoreText);
	window.display();
}
void PlayState::update() {
	Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
	if (backButton.getGlobalBounds().contains(mousePos)) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(255, 255, 255, 255));
}