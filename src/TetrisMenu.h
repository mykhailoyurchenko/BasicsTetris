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
	void updateCurrentTetris();
	void leftMove();
	void rightMove();
    bool isActive() const;        // Чи рухається фігура
    void rotateTetris();            // Поворот фігури
	bool rotatePressedLastFrame = false;    // Поворот фігури в останньому кадрі
    bool autoRotated = false;
    bool wasRotated = false;// Скинути стан гри
	int getScore() const { return score; }
	std::array<int, 4> getNextTetrises() const { return nextTetrises; }
	void resetScore() { score = 0; }
	void reset();
	void randomNextTetrises();


    void draw(RenderTarget& target, RenderStates states) const override;
    //gridType getGrid() { return grid; }
   
    std::array<std::array<Vector2i, 4>, 7> tetrisShapes;
    const std::array<Color, 7> tetrisColors = { Color::Cyan , Color::Blue, Color(240,160,0),
     Color::Yellow, Color::Green, Color(160,0,240), Color(240,0,0) };

private:
	int cols, rows, cellSize, originX, originY;
	std::array<int, 4> nextTetrises;
	gridType grid;
	std::vector<Vector2i> currentTetris; // Позиції поточної фігури
	Color currentColor;
	int currentType = -1;
	float moveInterval = 1.0f; // Інтервал спуску (сек)
	float moveTimer = 0.f;
	bool leftPressedLastFrame = false;
	bool rightPressedLastFrame = false;
	bool isMoving = false;
	int score = 0;

	bool canMove(int dx, int dy) const;
	void lockTetris();
	void clearTopRows();
	void clearFullRows();
};
