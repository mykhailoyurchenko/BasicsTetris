#include "Game.h"

GameOverState::GameOverState(Game& game): GameState(game),gameOverText(font, "Game Over", 80),mainMenuText(font, "Main Menu", 50)
{
	Vector2u winSize = game.getWindow().getSize();
	centerAll(gameOverText, mainMenuText);

	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition({ winSize.x * 0.5f, winSize.y * 0.4f });

	mainMenuText.setFillColor(Color::White);
	mainMenuText.setPosition({ winSize.x * 0.5f, winSize.y * 0.6f });
}

void GameOverState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
		if (mainMenuText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
		}
	}
}

void GameOverState::update(const Time&) {
	if (mainMenuText.getGlobalBounds().contains(game->getMousePos())) {
		mainMenuText.setFillColor(Color::Yellow);
	} else {
		mainMenuText.setFillColor(Color::White);
	}
}

void GameOverState::draw(sf::RenderWindow& window) {
	GameState::draw(window);
	window.draw(gameOverText);
	window.draw(mainMenuText);
}
