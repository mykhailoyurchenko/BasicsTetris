﻿#pragma once
#include "TetrisMenu.h"

template<typename Drawabletype> void centerOrigin(Drawabletype& drawable) {
	FloatRect bounds = drawable.getLocalBounds();
	drawable.setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
}
template<typename... Drawabletypes> void centerAll(Drawabletypes&... drawables) {
	(centerOrigin(drawables), ...);
}
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
	Text tetrisText;
};
class MenuState : public GameState {//Класс состояния игры
	Text quitButtonText;
	Text playButtonText;//Текст для кнопки play
public:
	MenuState(Game& game);//Передача посилання на поточну гру,для обробки подій
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class GameOverState : public GameState {
	Text gameOverText;
	Text mainMenuText;
public:
	GameOverState(Game& game);
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class PlayState : public GameState {//Класс состояния игры
	TetrisMenu& gameField;

	Text pauseButtonText;
	Text scoreText; // Текст для отображения очков
	Text scoreOutput;//Отображение набранных очков
	Text timeText;// Текст для відображення часу
	Text timeOutput;//Рахунок часу
	Text bestScoreOutput; // Найкращий рахунок 
	Text bestScoreText; // Текст найкращого рахунку
	
public:
	PlayState(Game& game);
 	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class PauseState : public PlayState {
	RectangleShape pauseOverlay;
	RectangleShape box;

	Text ResumeText;
	Text MainMenuText;
public:
	PauseState(Game& game);
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};