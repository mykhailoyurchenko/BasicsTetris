#pragma once
#include <SFML/Graphics.hpp>

struct CellData {
    int value;           // e.g., block type or 0 for empty
    sf::Color color;     // color of the cell
    // add more fields as needed
};

class TetrisMenu : public sf::Drawable {
public:
    TetrisMenu(int cols, int rows, int cellSize, int originX, int originY);

    void handleClick(const sf::Vector2f& mousePos, sf::Color newColor = sf::Color::Red);
	void drawTetris(int number);
	void moveTetris();
    // Draws the grid
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	auto getGrid() const { return grid; }

private:
    int cols, rows, cellSize, originX, originY;
    std::vector<std::vector<CellData>> grid;
   // std::array<std::array<Vector2f,4>,7> tetrises;
	//std::vector<sf::Vector2f> currentTetris; // Stores the current Tetris piece positions
    sf::Color currentColor; // Color of the current Tetris piece
    sf::Clock clock; // For timing movements
    float moveInterval; // Time interval for moving the Tetris piece
    bool isMoving; // Flag to check if the Tetris piece is moving
};