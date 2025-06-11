#include "Game.h"

GameOverState::GameOverState(Game& game)
	: GameState(game),
	  gameOverText(font, "Game Over", 80),
	  mainMenuText(font, "Main Menu", 50)
{
	Vector2u winSize = game.getWindow().getSize();
	centerAll(gameOverText, mainMenuText);

	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition({ winSize.x * 0.5f, winSize.y * 0.4f });

	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition({ winSize.x * 0.5f, winSize.y * 0.6f });
}

void GameOverState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
		if (mainMenuText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState(GameStateType::Menu);
		}
	}
}

void GameOverState::update(const sf::Time&) {
	if (mainMenuText.getGlobalBounds().contains(game->getMousePos())) {
		mainMenuText.setFillColor(sf::Color::Yellow);
	} else {
		mainMenuText.setFillColor(sf::Color::White);
	}
}

void GameOverState::draw(sf::RenderWindow& window) {
	GameState::draw(window);
	window.draw(gameOverText);
	window.draw(mainMenuText);
}
