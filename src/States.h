#pragma once
#include <SFML/Graphics.hpp>
#include <Game.h>

using namespace sf;

class GameState {
public:
	virtual void eventHandler(Event& event) {};
	virtual void update() {};
	virtual void draw(RenderWindow& window) {};
	virtual ~GameState() = default;
protected:
	GameState(Game& game);
	Game* game;
	Texture backgroundTexture;
	Sprite background;
	Font font;
	Font tetrisFont;
	Text tetrisText;
};
class MenuState : public GameState {
	RectangleShape playButton;
	Text playButtonText;
public:
	MenuState(Game& game);
	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;

};
class PlayState : public GameState {
	RectangleShape game;
	RectangleShape backButton;
	Text backButtonText;
	Text scoreText;
public:
	PlayState();
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};