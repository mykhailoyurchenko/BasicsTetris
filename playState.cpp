#include "Game.h"

// Êîíñòóêòîð êëàñó PlayState
PlayState::PlayState(Game& game) : GameState(game), backButton(Vector2f(150, 50)),
backButtonText(font, "Go back", 50), scoreText(font, "0", 40) {
	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1740, 40));

	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));

	gameField.setSize(Vector2f(500, 800));
	gameField.setPosition(Vector2f(700, 150));
	gameField.setFillColor(Color::Black);

	gameFieldNext.setSize(Vector2f(230,600));
	gameFieldNext.setPosition(Vector2f(1200, 150));
	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
}
//ïåðåâ³ðêà íà âçàºìîä³þ ç êíîïêîþ
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (backButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
		}
	}
}
// ðåíäåð
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);
	window.draw(gameField);
	window.draw(gameFieldNext);
	window.draw(backButton);
	window.draw(backButtonText);
	window.draw(scoreText);
}
// çì³íà êîë³ð òåêñòó êíîïêè ïðè íàâåäåíí³ ìèø³
void PlayState::update() {
	GameState::update();

	if (backButton.getGlobalBounds().contains(game->getMousePos())) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(Color::White));
}