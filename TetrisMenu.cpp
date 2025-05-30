#include <TetrisMenu.h>
#include <SFML/Graphics.hpp>

using namespace sf;

void TetrisMenu::handleClick(const Vector2f& mousePos, Color newColor) {
    int col = (mousePos.x - originX) / cellSize;
    int row = (mousePos.y - originY) / cellSize;
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        grid[col][row].color = newColor;
    }
}

TetrisMenu::TetrisMenu(int cols, int rows, int cellSize, int originX, int originY)
    : cols(cols), rows(rows), cellSize(cellSize), originX(originX), originY(originY) {
    grid.resize(cols, std::vector<CellData>(rows, { 0, Color::Black }));
}

void TetrisMenu::draw(RenderTarget& target, RenderStates states) const {
    sf::RectangleShape cell(Vector2f(cellSize, cellSize));
    cell.setOutlineColor(Color(32, 31, 31));
    cell.setOutlineThickness(1.f);
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            cell.setPosition(Vector2f(originX + x * cellSize, originY + y * cellSize));
            cell.setFillColor(grid[x][y].color);
            target.draw(cell, states);
        }
    }
}


