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
	timeText.setPosition({ winSize.x * 0.82f, winSize.y * 0.83f });

	//Лічильник часу
	timeOutput.setFillColor(Color::White);
	timeOutput.setPosition({ winSize.x * 0.82f, winSize.y * 0.88f });

	//Лічільник найкращого результату
	bestScoreOutput.setFillColor(Color::White);
	bestScoreOutput.setPosition({ winSize.x * 0.87f, winSize.y * 0.78f });

	// текст найкращого результату
	bestScoreText.setFillColor(Color::White);
	bestScoreText.setPosition({ winSize.x * 0.81f, winSize.y * 0.78f });

	gameFieldNext.setFillColor(Color(0, 255, 0, 150));
	gameFieldNext.setPosition({ winSize.x * 0.68f, winSize.y * 0.40f });
}

gridType* PlayState::getGrid() {
	return gameField.getGrid();
};

//перевірка на взаємодію з кнопкою
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {

		if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState(GameStateType::Pause);
			return;
		}
	}
	const auto* keyboardEvent = event.getIf<Event::KeyPressed>();
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::S || keyboardEvent->code == Keyboard::Key::Down)) {
		gameField.update(2.5);
	}
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::D || keyboardEvent->code == Keyboard::Key::Right)) {
		gameField.handleHorizontalInput();
	}
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::A || keyboardEvent->code == Keyboard::Key::Left)) {
		gameField.handleHorizontalInput();
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
		int randomTetris = rand() % 7;
		gameField.spawnTetris(randomTetris);
	}
	else {
		gameField.update(delta.asSeconds());
	}

	// Очищення кольору у верхніх двох рядах

// 	if (game->getClock().getElapsedTime() >= seconds(5)) {
// 		grid.fill(std::array<CellData, 20>{});
// 		gameField.drawTetris(rand() % 7);

// 		game->getClock().restart();
// 	}

	if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else pauseButtonText.setFillColor(Color::White);
}
