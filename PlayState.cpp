#include "Game.h"
#include <random>

// Констуктор класу PlayState

PlayState::PlayState(Game& game) : GameState(game), gameField(game.getGrid(), 40, 750, 100), gameFieldNext(Vector2f(230, 600)),
scoreText(font, "Score:", 40),scoreOutput(font, "0", 40), timeText(font, "Time:", 40), timeOutput(font, "00:00:00", 40),
bestScoreOutput(font, "0", 40), bestScoreText(font, "Best Score:", 40), pauseButton(Vector2f(150, 50)), pauseButtonText(font, "Pause", 40) {
	sf::Vector2u winSize = game.getWindow().getSize();
	// кнопка паузи
	pauseButton.setFillColor(Color(0, 0, 0, 0.0));
	Vector2f pausePosition(winSize.x * 0.95, winSize.y * 0.2);
	pauseButton.setPosition(pausePosition);
	centerOrigin(pauseButton);

	// текст кнопки паузи
	pauseButtonText.setFillColor(Color::White);
	pauseButtonText.setPosition(pausePosition);
	centerOrigin(pauseButtonText);

	//Лічильник для підрахунку очков
	scoreOutput.setFillColor(Color::White);
	Vector2f scoreOutputPosition(winSize.x * 0.83, winSize.y * 0.73);
	scoreOutput.setPosition(scoreOutputPosition);
	centerOrigin(scoreOutput);

	//Текст для підрахунку очков
	scoreText.setFillColor(Color::White);
	Vector2f scoreTextPosition(winSize.x * 0.79, winSize.y * 0.73);
	scoreText.setPosition(scoreTextPosition);
	centerOrigin(scoreText);

	//Текст часу
	timeText.setFillColor(Color::White);
	Vector2f timeTextPosition(winSize.x * 0.82, winSize.y * 0.83);
	timeText.setPosition(timeTextPosition);
	centerOrigin(timeText);

	//Лічильник часу
	timeOutput.setFillColor(Color::White);
	Vector2f timeOutputPosition(winSize.x * 0.82, winSize.y * 0.88);
	timeOutput.setPosition(timeOutputPosition);
	centerOrigin(timeOutput);

	//Лічільник найкращого результату
	bestScoreOutput.setFillColor(Color::White);
	Vector2f bestScoreOutputPosition(winSize.x * 0.87, winSize.y * 0.78);
	bestScoreOutput.setPosition(bestScoreOutputPosition);
	centerOrigin(bestScoreOutput);

	// текст найкращого результату
	bestScoreText.setFillColor(Color::White);
	Vector2f bestScoreTextPosition(winSize.x * 0.81, winSize.y * 0.78);
	bestScoreText.setPosition(bestScoreTextPosition);
	centerOrigin(bestScoreText);

	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
	Vector2f gameFieldNextPosition(winSize.x * 0.68, winSize.y * 0.40);
	gameFieldNext.setPosition(gameFieldNextPosition);
	centerOrigin(gameFieldNext);
}

//перевірка на взаємодію з кнопкою
gridType* PlayState::getGrid() {
	return gameField.getGrid();
};
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		
		if (pauseButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState(GameStateType::Pause);
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
void PlayState::update(const Time& delta) {
	GameState::update();
	srand(time(0));
	int randomTetris = rand() % 7;
	gameField.drawTetris(randomTetris);

	if (pauseButton.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else pauseButtonText.setFillColor(Color::White);
}
