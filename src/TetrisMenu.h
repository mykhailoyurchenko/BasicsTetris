#pragma once
#include <SFML/Graphics.hpp>
//#include <array>
//#include <vector>

using namespace sf;

struct CellData {
	int x = 0;
	int y = 0;
	Color color = Color::Black;
	bool isFull = 0;
};

class TetrisMenu : public Drawable {
public:
	TetrisMenu(Vector2u winSize);
	static constexpr std::array<std::array<Vector2i, 4>, 7> tetrisShapes = { {
			// I
			{{{0,0}, {2,0}, {1,0}, {3,0}}},
			// J
			{{{0,0}, {0,1}, {1,1}, {2,1}}},
			// L
			{{{2,0}, {0,1}, {1,1}, {2,1}}},
			// O
			{{{0,0}, {1,0}, {0,1}, {1,1}}},
			// S
			{{{1,0}, {2,0}, {1,1}, {0,1}}},
			// T
			{{{1,0}, {0,1}, {1,1}, {2,1}}},
			// Z
			{{{0,0}, {1,0}, {1,1}, {2,1}}}
		} };
	static constexpr std::array<Color, 7> tetrisColors = { Color::Cyan,Color::Blue,
		Color(240,160,0),Color::Yellow,Color::Green,Color(160,0,240),Color(240,0,0) };


	void spawnTetris(); // Створити нову фігуру
	void update(float delta);     // Оновлення позиції фігури
	void clearFullRows();
	void tetrisesShift();
	void updateCurrentTetris();
	void move(int dx);
	void rotateTetris();            // Поворот фігури

	void setUpHeld(bool upHelded) { upHeld = upHelded; }
	void addToElapsedTime(float delta) { elapsedTime += delta; }

	bool canMove(int dx, int dy) const;
	bool isActive() const { return isMoving; } // Чи рухається фігура
	bool isGameOver() const;
	bool isUpHelded() const { return upHeld; }

	int getScore() const { return score; }
	float getElapsedTime() const { return elapsedTime; }
	std::array<int, 4> getNextTetrises() const { return nextTetrises; }
	float getSpeedByScore(int score);

	void draw(RenderTarget& target, RenderStates states) const override;
	void drawNextTetrises(RenderTarget& target) const;


private:
	static constexpr int cols = 10, rows = 20, cellSize = 40, originX = 750, originY = 100;
	std::array<std::array<CellData, rows>, cols> grid;

	std::array<Vector2i, 4> currentTetris; // Позиції поточної фігури
	std::array<int, 4> nextTetrises;

	Color currentColor;
	int currentType = -1;
	int score = 0;

	RectangleShape gameFieldNext;//Поле для следующих фигур

	float moveInterval = 1.0f; // Інтервал спуску (сек)
	float moveTimer = 0.f;
	float elapsedTime = 0.f;
	bool isMoving = false;
	bool upHeld = false;

	void lockTetris();
};