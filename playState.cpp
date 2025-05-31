#include "Game.h"

// Констуктор класу PlayState
PlayState::PlayState(Game& game) : GameState(game), gameField(10, 20, 40, 750, 100), gameFieldNext(Vector2f(230, 600)), backButton(Vector2f(150, 50)),
backButtonText(font, "Go back", 50), scoreText(font, "0", 40), scoreOutput(font, "0", 40), timeText(font, "Time:", 40), timeOutput(font, "00:00:00", 40), 
bestScoreOutput(font, "0", 40), bestScoreText(font, "Best Score:", 40),quitButton(Vector2f(150,50)),quitButtonText(font,"Quit",40),pauseButton(Vector2f(150,50)),pauseButtonText(font,"Pause",40){


	quitButton.setFillColor(Color(0.0, 0, 0, 0.0));
	quitButton.setPosition(Vector2f(1750, 200));
	quitButtonText.setFillColor(Color::White);
	quitButtonText.setPosition(Vector2f(1770, 200));

	pauseButton.setFillColor(Color(0, 0, 0.0, 0.0));
	pauseButton.setPosition(Vector2f(1600, 20));
	pauseButtonText.setFillColor(Color::White);
	pauseButtonText.setPosition(Vector2f(1610, 200));

	


	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1740, 40));

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
void PlayState::eventHandler(Event& event) {
	GameState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (backButton.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
			return;
		}
		if (pauseButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PauseState>();
			return;
		}
		if (quitButtonText.getGlobalBounds().contains(game->getMousePos())) {
			game->getWindow().close();
		}
	}
}
// рендер
void PlayState::draw(RenderWindow& window) {
	GameState::draw(window);

	window.draw(quitButton);
	window.draw(quitButtonText);
	window.draw(pauseButton);
	window.draw(pauseButtonText);

	window.draw(backButton);
	window.draw(backButtonText);
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

	if (quitButton.getGlobalBounds().contains(game->getMousePos())) {
		quitButtonText.setFillColor(Color::Yellow);
	}
	else {
		quitButtonText.setFillColor(Color::White);
	}
	if (pauseButton.getGlobalBounds().contains(game->getMousePos())) {
		pauseButtonText.setFillColor(Color::Yellow);
	}
	else{
		pauseButtonText.setFillColor(Color::White);
	}
	// gameField.drawTetris();
	if (backButton.getGlobalBounds().contains(game->getMousePos())) {
		backButtonText.setFillColor(Color::Yellow);
	}
	else backButtonText.setFillColor(Color(255, 255, 255, 255));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		gameField.handleClick(game->getMousePos(), Color::Red);
	}
}
