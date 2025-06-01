#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisMenu.h"
using namespace sf;
//using gridType = std::vector<std::vector<CellData>>;

template<typename Drawabletype>
void centerOrigin(Drawabletype& drawable) {
	FloatRect bounds = drawable.getLocalBounds();
	drawable.setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
}

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
	RectangleShape quitButton;
	
	Text quitButtonText;
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

	RectangleShape pauseButton;

	Text pauseButtonText;

	Text scoreText; // Текст для отображения очков
	Text scoreOutput;//Отображение набранных очков
	Text timeText;// Текст для відображення часу
	Text timeOutput;//Рахунок часу
	Text bestScoreOutput; // Найкращий рахунок 
	Text bestScoreText; // Текст найкращого рахунку

public:
	PlayState(Game& game);
	gridType getField();
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};
class PauseState : public PlayState {
	RectangleShape pauseOverlay;
	
	Text ResumeText;
	Text MainMenuText;
	RectangleShape box;

public:
	PauseState(Game& game);
	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};