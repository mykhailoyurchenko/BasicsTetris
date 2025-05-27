#pragma once
#include <SFML/Graphics.hpp>
#include <Game.h>

using namespace sf;

class GameState {//Базовый класс
public:
	virtual void eventHandler(Event& event) {};//Обновление действий
	virtual void update() {};//Обновление значений и рендер
	virtual void draw(RenderWindow& window) {};//Отрисовка
	virtual ~GameState() = default;//Деструктор
protected://Конструктор для классу Game 
	GameState(Game& game);
	Game* game;//Указатель на обьект Game 
	Texture backgroundTexture;//Визуал
	Sprite background;//Визуал
	Font font;//Визуал
	Font tetrisFont;//Визуал
	Text tetrisText;//Визуал
};
class MenuState : public GameState {//Класс для меню игры
	RectangleShape playButton;//Кнопка
	Text playButtonText;//Текст для кнопки play 
public://Конструктор 
	MenuState(Game& game);
	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;

};
class PlayState : public GameState {//Класс для игры
	RectangleShape game;//Игровое поле
	RectangleShape backButton;//Кнопка возварата в меню 
	Text backButtonText;//Текст для возварата
	Text scoreText;//Отображение набранных очков
public:
	PlayState();//Конструктор
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};