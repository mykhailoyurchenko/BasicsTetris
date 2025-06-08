#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

using namespace sf;

struct CellData {
	int x = 0;
	int y = 0;
	Color color = Color::Black;
	bool isFull = 0;
};

using gridType = std::array<std::array<CellData, 20>, 10>;

class TetrisMenu : public Drawable {
public:
	TetrisMenu(int cellSize, int originX, int originY);

	void spawnTetris(); // Створити нову фігуру
	void update(float delta);     // Оновлення позиції фігури
	void clearFullRows();
	void tetrisesShift();
	void updateCurrentTetris();
	void leftMove();
	void rightMove();
	void rotateTetris();            // Поворот фігури

	bool canMove(int dx, int dy) const;
	bool isActive() const { return isMoving; } // Чи рухається фігура

	int getScore() const { return score; }
	std::array<int, 4> getNextTetrises() const { return nextTetrises; }
	void resetScore() { score = 0; }
	//void reset();
	float getElapsedTime() const { return elapsedTime; }



	void draw(RenderTarget& target, RenderStates states) const override;

	std::array<std::array<Vector2i, 4>, 7> tetrisShapes;
	const std::array<Color, 7> tetrisColors = { Color::Cyan,Color::Blue,
		Color(240,160,0),Color::Yellow,Color::Green,Color(160,0,240),Color(240,0,0)};

private:
	int cols, rows, cellSize, originX, originY;
	gridType grid;

	std::vector<Vector2i> currentTetris; // Позиції поточної фігури
	std::array<int, 4> nextTetrises;

	Color currentColor;
	int currentType = -1;
	int score = 0;

	float moveInterval = 1.0f; // Інтервал спуску (сек)
	float moveTimer = 0.f;
	bool isMoving = false;
	bool autoRotated = false;
  int score = 0;
	float elapsedTime = 0.f; 
	void lockTetris();
	void clearTopRows();
};
