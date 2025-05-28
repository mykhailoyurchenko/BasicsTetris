#pragma once
#include <SFML/Graphics.hpp>
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
	RectangleShape gameField;//Игровое поле
	RectangleShape backButton;//Кнопка возварата в меню 
	Text backButtonText;//Текст для возварата
	Text scoreText;//Отображение набранных очков
public:
	PlayState(Game& game);
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};