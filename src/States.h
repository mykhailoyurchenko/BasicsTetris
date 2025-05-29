#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisMenu.h"
using namespace sf;

class Game;


class GameState {//Базовый класс
public:
	virtual void eventHandler(Event& event);//Обновление действий
	virtual void update() {};//Обновление значений и рендер
	virtual void draw(RenderWindow& window);//Отрисовка
	virtual ~GameState() = default;//Деструктор
protected://Поля дочірніх класів GameState
	GameState(Game& game);
	Game* game;//Указатель на обьект классу Game
	//Визуал
	Texture backgroundTexture;
	Sprite* backgroundSprite;
	Font font;
	Font tetrisFont;
	Text tetrisText;
};
class MenuState : public GameState {//Класс состояния игры
	RectangleShape playButton;//Кнопка
	Text playButtonText;//Текст для кнопки play 
public:
	MenuState(Game& game);//Передача посилання на поточну гру,для обробки подій
	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;

};
class PlayState : public GameState {//Класс состояния игры
	TetrisMenu gameField;//Игровое поле
	RectangleShape gameFieldNext;//Поле для следующих фигур
	RectangleShape backButton;//Кнопка возварата в меню 
	Text backButtonText;//Текст для возварата
	Text scoreText; // Текст для отображения очков
	Text scoreOutur;//Отображение набранных очков
	Text timeText;// Текст для відображення часу
	Text timeOutur;//Рахунок часу
	Text bestScoreOutur; // Найкращий рахунок 
	Text bestScoreText; // Текст найкращого рахунку

public:
	PlayState(Game& game);
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};