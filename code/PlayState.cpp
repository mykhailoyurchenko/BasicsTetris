#include "Game.h"
#include <random>

// Констуктор класу PlayState

PlayState::PlayState(Game& game) : GameState(game), gameField(game.getGrid(), 40, 750, 100), gameFieldNext(Vector2f(230, 600)),
scoreText(font, "Score:", 40), scoreOutput(font, "0", 40), timeText(font, "Time:", 40), timeOutput(font, "00:00:00", 40),
bestScoreOutput(font, "0", 40), bestScoreText(font, "Best Score:", 40), pauseButtonText(font, "Pause", 40) {
	Vector2u winSize = game.getWindow().getSize();
	centerAll(pauseButtonText, scoreOutput, scoreText, timeText, timeOutput, bestScoreOutput, bestScoreText, gameFieldNext);

	// текст кнопки паузи
	pauseButtonText.setFillColor(Color::White);
	pauseButtonText.setPosition({ winSize.x * 0.95f, winSize.y * 0.2f });

	//Лічильник для підрахунку очков
	scoreOutput.setFillColor(Color::White);
	scoreOutput.setPosition({ winSize.x * 0.83f, winSize.y * 0.73f });

	//Текст для підрахунку очков
	scoreText.setFillColor(Color::White);
	scoreText.setPosition({ winSize.x * 0.79f, winSize.y * 0.73f });

	//Текст часу
	timeText.setFillColor(Color::White);
	Vector2f timeTextPosition({ winSize.x * 0.82f, winSize.y * 0.83f });
	timeText.setPosition(timeTextPosition);

	//Лічильник часу
	timeOutput.setFillColor(Color::White);
	Vector2f timeOutputPosition({ winSize.x * 0.82f, winSize.y * 0.88f });
	timeOutput.setPosition(timeOutputPosition);

	//Лічільник найкращого результату
	bestScoreOutput.setFillColor(Color::White);
	Vector2f bestScoreOutputPosition({ winSize.x * 0.87f, winSize.y * 0.78f });
	bestScoreOutput.setPosition(bestScoreOutputPosition);

	// текст найкращого результату
	bestScoreText.setFillColor(Color::White);
	Vector2f bestScoreTextPosition({ winSize.x * 0.81f, winSize.y * 0.78f });
	bestScoreText.setPosition(bestScoreTextPosition);

	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
	Vector2f gameFieldNextPosition({ winSize.x * 0.68f, winSize.y * 0.40f });
	gameFieldNext.setPosition(gameFieldNextPosition);
}

gridType* PlayState::getGrid() {
	return gameField.getGrid();
};

//перевірка на взаємодію з кнопкою
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	const auto* keyboardEvent = event.getIf<Event::KeyPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {

		if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState(GameStateType::Pause);
			return;
		}
	}
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::S || keyboardEvent->code == Keyboard::Key::Down)) {
		gameField.update(5.0);
	}
}
// рендер
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);

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
	gridType& grid = game->getGrid();

	// Рух фігури донизу кожної секунди
	if (!gameField.isActive()) {
		gameField.spawnTetris(rand() % 7);
	}
	else {
		gameField.update(delta.asSeconds());
	}

	// Очищення кольору у верхніх двох рядах

// 	if (game->getClock().getElapsedTime() >= seconds(5)) {
// 		grid.fill(std::array<CellData, 20>{});
// 		game->getClock().restart();
// 	}
	if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else pauseButtonText.setFillColor(Color::White);
}
