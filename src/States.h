#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Game;


class GameState {//������� �����
public:
	virtual void eventHandler(Event& event);//���������� ��������
	virtual void update() {};//���������� �������� � ������
	virtual void draw(RenderWindow& window);//���������
	virtual ~GameState() = default;//����������
protected://���� ������� ����� GameState
	GameState(Game& game);
	Game* game;//��������� �� ������ ������ Game 
	//������
	Texture backgroundTexture;
	Font font;
	Font tetrisFont;
	Text tetrisText;
};
class MenuState : public GameState {//����� ��������� ����
	RectangleShape playButton;//������
	Text playButtonText;//����� ��� ������ play 
public:
	MenuState(Game& game);//�������� ��������� �� ������� ���,��� ������� ����
	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;

};
class PlayState : public GameState {//����� ��������� ����
	RectangleShape gameField;//������� ����
	RectangleShape backButton;//������ ��������� � ���� 
	Text backButtonText;//����� ��� ���������
	Text scoreText;//����������� ��������� �����
public:
	PlayState(Game& game);
 	void eventHandler(Event& event) override;
	void update() override;
	void draw(RenderWindow& window) override;
};