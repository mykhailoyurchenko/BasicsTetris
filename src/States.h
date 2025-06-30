#pragma once
#include "TetrisMenu.h"
#include "Button.h"

class Game;

class GameState {//Базовый класс
public:
	virtual void eventHandler(Event& event);//Обновление действий
	virtual void update(const Time& delta = Time::Zero) {};//Обновление значений и рендер
	virtual void draw(RenderWindow& window);//Отрисовка
	virtual ~GameState() = default;//Деструктор
protected://Поля дочірніх класів GameState
	GameState(Game& game);
	Game* game;//Указатель на обьект классу Game
	//Визуал
	Texture backgroundTexture;
	std::unique_ptr<Sprite> backgroundSprite;
	Font font;
	Font tetrisFont;
	Button tetrisText;
};
class MenuState : public GameState {//Класс состояния игры
	Button quitButtonText;
	Button playButtonText;//Текст для кнопки play
public:
	MenuState(Game& game);//Передача посилання на поточну гру,для обробки подій
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class GameOverState : public GameState {
	Button gameOverText;
	Button mainMenuText;
public:
	GameOverState(Game& game);
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class PlayState : public GameState {//Класс состояния игры
	TetrisMenu& gameField;

	Button pauseButtonText;
	Button scoreText; // Текст для отображения очков
	Button scoreOutput;//Отображение набранных очков
	Button timeText;// Текст для відображення часу
	Button timeOutput;//Рахунок часу
	Button bestScoreOutput; // Найкращий рахунок 
	Button bestScoreText; // Текст найкращого рахунку
	
public:
	PlayState(Game& game);
 	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class PauseState : public PlayState {
	RectangleShape pauseOverlay;
	RectangleShape box;

	Button ResumeText;
	Button MainMenuText;
public:
	PauseState(Game& game);
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};