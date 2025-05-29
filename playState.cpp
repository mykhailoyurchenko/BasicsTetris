#include "Game.h"

// Констуктор класу PlayState
PlayState::PlayState(Game& game) : GameState(game), gameField(24, 16, 25, 750, 100), gameFieldNext(Vector2f(230, 600)), backButton(Vector2f(150, 50)),
backButtonText(font, "Go back", 50), scoreText(font, "0", 40),, scoreOutur(font, "0", 40), timeText(font, "Time:", 40), timeOutur(font, "00:00:00", 40), 
bestScoreOutur(font, "0", 40), bestScoreText(font, "Best Score:", 40) {

	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1740, 40));

	//Лічильник для підрахунку очков
	scoreOutur.setFillColor(Color::White);
	scoreOutur.setPosition(Vector2f(1617, 752));

	//Текст для підрахунку очков
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(1507, 750));

	//Текст часу
	timeText.setFillColor(Color::White);
	timeText.setPosition(Vector2f(1520, 900));

	//Лічильник часу
	timeOutur.setFillColor(Color::White);
	timeOutur.setPosition(Vector2f(1500, 960));

	//Лічільник найкращого результату
	bestScoreOutur.setFillColor(Color::White);
	bestScoreOutur.setPosition(Vector2f(1665, 827));

	// текст найкращого результату
	bestScoreText.setFillColor(Color::White);
	bestScoreText.setPosition(Vector2f(1472, 825));

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
	window.draw(scoreOutur);
	window.draw(timeText);
	window.draw(timeOutur);
	window.draw(bestScoreText);
	window.draw(bestScoreOutur);

}
// зміна колір тексту кнопки при наведенні миші
void PlayState::update() {
	GameState::update();
	if (backButton.getGlobalBounds().contains(game->getMousePos())) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(255, 255, 255, 255));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		gameField.handleClick(game->getMousePos(), sf::Color::Red);
	}
}
