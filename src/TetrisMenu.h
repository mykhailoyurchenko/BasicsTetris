#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

struct CellData {
	int x = 0;
	int y = 0;
	sf::Color color = sf::Color::Black;
	bool isFull = 0;
};

using gridType = std::array<std::array<CellData, 20>, 10>;

class TetrisMenu : public sf::Drawable {
public:
	TetrisMenu(gridType& grid, int cellSize, int originX, int originY);

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
	void randomNextTetrises();

	


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    gridType* getGrid() const { return &grid; }
    std::array<int, 4> nextTetrises;

    std::array<std::array<sf::Vector2i, 4>, 7> tetrisShapes;
    const std::array<sf::Color, 7> tetrisColors = { sf::Color::Cyan , sf::Color::Blue, sf::Color(240,160,0),
     sf::Color::Yellow, sf::Color::Green, sf::Color(160,0,240), sf::Color(240,0,0) };

private:
	int cols, rows, cellSize, originX, originY;
	gridType& grid;
	std::vector<sf::Vector2i> currentTetris; // Позиції поточної фігури
	sf::Color currentColor;
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
