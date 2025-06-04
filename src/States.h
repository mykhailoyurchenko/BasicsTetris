#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisMenu.h"
using namespace sf;

template<typename Drawabletype> void centerOrigin(Drawabletype& drawable) {
	FloatRect bounds = drawable.getLocalBounds();
	drawable.setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
}
template<typename... Ts> void centerAll(Ts&... drawables) {
	(centerOrigin(drawables), ...);
}
class Game;

class GameState {//Базовый класс
public:
	virtual void eventHandler(Event& event);//Обновление действий
	virtual void update(const Time& delta = Time::Zero) {};//Обновление значений и рендер
	virtual void draw(RenderWindow& window);//Отрисовка
	virtual ~GameState() = default;//Деструктор
	virtual gridType* getGrid() { return nullptr; }

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
	Text quitButtonText;
	Text playButtonText;//Текст для кнопки play 
public:
	MenuState(Game& game);//Передача посилання на поточну гру,для обробки подій
	void eventHandler(Event& event) override;
	void update(const Time& delta = Time::Zero) override;
	void draw(RenderWindow& window) override;
};
class PlayState : public GameState {//Класс состояния игры
	TetrisMenu gameField;//Игровое поле
	RectangleShape gameFieldNext;//Поле для следующих фигур

	Text pauseButtonText;
	Text scoreText; // Текст для отображения очков
	Text scoreOutput;//Отображение набранных очков
	Text timeText;// Текст для відображення часу
	Text timeOutput;//Рахунок часу
	Text bestScoreOutput; // Найкращий рахунок 
	Text bestScoreText; // Текст найкращого рахунку

public:
	PlayState(Game& game);
	gridType* getGrid() override;
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