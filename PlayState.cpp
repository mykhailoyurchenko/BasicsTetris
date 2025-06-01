#include "Game.h"

// Констуктор класу PlayState
PlayState::PlayState(Game& game) : GameState(game), gameField(40, 750, 100), gameFieldNext(Vector2f(230, 600)),
scoreText(font, "0", 40),scoreOutput(font, "0", 40), timeText(font, "Time:", 40), timeOutput(font, "00:00:00", 40),
bestScoreOutput(font, "0", 40), bestScoreText(font, "Best Score:", 40), pauseButton(Vector2f(150, 50)), pauseButtonText(font, "Pause", 40) {

	pauseButton.setFillColor(Color(0, 0, 0, 0.0));
	pauseButton.setPosition(Vector2f(1750, 200));

	pauseButtonText.setFillColor(Color::White);
	pauseButtonText.setPosition(Vector2f(1750, 200));

	//Лічильник для підрахунку очков
	scoreOutput.setFillColor(Color::White);
	scoreOutput.setPosition(Vector2f(1617, 752));

	//Текст для підрахунку очков
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(1507, 750));

	//Текст часу
	timeText.setFillColor(Color::White);
	timeText.setPosition(Vector2f(1520, 900));

	//Лічильник часу
	timeOutput.setFillColor(Color::White);
	timeOutput.setPosition(Vector2f(1500, 960));

	//Лічільник найкращого результату
	bestScoreOutput.setFillColor(Color::White);
	bestScoreOutput.setPosition(Vector2f(1665, 827));

	// текст найкращого результату
	bestScoreText.setFillColor(Color::White);
	bestScoreText.setPosition(Vector2f(1472, 825));

	gameFieldNext.setPosition(Vector2f(1200, 150));
	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
}

//перевірка на взаємодію з кнопкою
//gridType PlayState::getField() {
//	return gameField.getGrid();
//};
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		
		if (pauseButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PauseState>();
			return;
		}
	}
}
// рендер
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);
	window.draw(pauseButton);
	window.draw(pauseButtonText);

	
	window.draw(gameField);
	window.draw(gameFieldNext);

	window.draw(scoreText);
	window.draw(scoreOutput);
	window.draw(timeText);
	window.draw(timeOutput);
	window.draw(bestScoreText);
	window.draw(bestScoreOutput);
}
// зміна колір тексту кнопки при наведенні миші
void PlayState::update() {
	GameState::update();
	gameField.drawTetris(5);

	if (pauseButton.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else pauseButtonText.setFillColor(Color::White);
}
