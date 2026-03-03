#include "Game.h"

GameOverState::GameOverState(Game& game) : GameState(game), gameOverText(font, "Game Over", 80), mainMenuText(font, "Main Menu", 50)
{
	Vector2u winSize = game.getWindow().getSize();

	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition({ winSize.x * 0.5f, winSize.y * 0.4f });

	mainMenuText.setPosition({ winSize.x * 0.5f, winSize.y * 0.6f });
}

void GameOverState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	if (mainMenuText.isClicked(game->getMousePos(), event)) {
		game->setState<MenuState>();
	}
}

void GameOverState::update(const Time&) {
	mainMenuText.update(game->getMousePos());
}

void GameOverState::draw(sf::RenderWindow& window) {
	GameState::draw(window);
	window.draw(gameOverText);
	window.draw(mainMenuText);
}