#pragma once
#include <SFML/Graphics.hpp>
#include <array>

struct CellData {
	int x;
    int y;
    sf::Color color = sf::Color::Black;     // color of the cell
    bool isFull = 0;
    // add more fields as needed
};

using gridType = std::array<std::array<CellData, 20>, 10>;

class TetrisMenu : public sf::Drawabletype {
public:
    TetrisMenu(int cellSize, int originX, int originY);

	void drawTetris(int number);
	void moveTetris();
    // Draws the grid
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
     gridType getGrid() const { return grid; }

private:
    int cols, rows, cellSize, originX, originY;
    gridType grid;
    std::array<std::array<CellData,4>,7> tetrises;
	std::vector<sf::Vector2f> currentTetris; // Stores the current Tetris piece positions
    sf::Color currentColor; // Color of the current Tetris piece
    sf::Clock clock; // For timing movements
    float moveInterval; // Time interval for moving the Tetris piece
    bool isMoving; // Flag to check if the Tetris piece is moving
};