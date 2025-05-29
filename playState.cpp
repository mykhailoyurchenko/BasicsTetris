#include "Game.h"
// Констуктор класу PlayState
PlayState::PlayState(Game& game) : GameState(game),gameField(24, 16, 25, 750, 100), gameFieldNext(Vector2f(230,600)), backButton(Vector2f(150, 50)),
backButtonText(font, "Go back", 50), scoreText(font, "0", 40) {
	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1740, 40));

	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));

	gameFieldNext.setPosition(Vector2f(1200, 150));
	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
}

//перевірка на взаємодію з кнопкою
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (backButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
		}
	}



}
// рендер
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);
	window.draw(backButton);
	window.draw(backButtonText);
	window.draw(gameField);
	window.draw(gameFieldNext);
	window.draw(scoreText);
	
	
}
// зміна колір тексту кнопки при наведенні миші
void PlayState::update() {
	GameState::update();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		gameField.handleClick(game->getMousePos(), sf::Color::Red);

	if (backButton.getGlobalBounds().contains(game->getMousePos())) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(255, 255, 255, 255));
}

