#include "Game.h"
#include <iomanip>
#include <sstream>
//#include <random>

// Констуктор класу PlayState

PlayState::PlayState(Game& game) : GameState(game),scoreText(font, "Score:", 40), scoreOutput(font, "0", 40), 
timeText(font, "Time:", 40), timeOutput(font, "00:00:00", 40),bestScoreOutput(font, "0", 40), 
bestScoreText(font, "Best Score:", 40), pauseButtonText(font, "Pause", 40) {
	Vector2u winSize = game.getWindow().getSize();
	centerAll(pauseButtonText, scoreOutput, scoreText, timeText, timeOutput, bestScoreOutput, bestScoreText);

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
}

//перевірка на взаємодію з кнопкою
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	
	const auto* keyboardEvent = event.getIf<Event::KeyPressed>();
	TetrisMenu& gameField = game->getField();

	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::W ||
      keyboardEvent->code == Keyboard::Key::Up) && !gameField.isUpHelded()) {
		gameField.rotateTetris();
		gameField.setUpHeld(true);
	}
	else if (auto* kr = event.getIf<sf::Event::KeyReleased>()) {
		if (kr->code == sf::Keyboard::Key::W || kr->code == sf::Keyboard::Key::Up) {
			gameField.setUpHeld(false);
		}
	}

	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::S || 
		keyboardEvent->code == Keyboard::Key::Down)) {
		gameField.update(5.0);
	}
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::D || 
		keyboardEvent->code == Keyboard::Key::Right)) {
		gameField.rightMove();
	}
	if (keyboardEvent && (keyboardEvent->code == Keyboard::Key::A || 
		keyboardEvent->code == Keyboard::Key::Left)) {
		gameField.leftMove();
	}

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PauseState>();
		}
	}
}
void PlayState::draw(RenderWindow& window) {  
    GameState::draw(window);

    window.draw(pauseButtonText);  
    window.draw(game->getField());
	
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
	TetrisMenu& gameField = game->getField();
	// Рух фігури донизу кожної секунди
	gameField.elapsedTime += delta.asSeconds();

	if (!gameField.isActive()) {
		gameField.tetrisesShift();
		gameField.spawnTetris();
		if (gameField.isGameOver()) {
			game->setState<GameOverState>();
			return;
		}
	}
	else {
		gameField.update(delta.asSeconds());
	}
	
	// Оновлення очок
	scoreOutput.setString(to_string(gameField.getScore()));


		//час
	int totalSeconds = static_cast<int>(gameField.getElapsedTime());
	int hours = totalSeconds / 3600;
	int minutes = (totalSeconds % 3600) / 60;
	int seconds = totalSeconds % 60;

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << hours << ":"
	    << std::setw(2) << std::setfill('0') << minutes << ":"
	    << std::setw(2) << std::setfill('0') << seconds;
	timeOutput.setString(oss.str());

	if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else pauseButtonText.setFillColor(Color::White);
}