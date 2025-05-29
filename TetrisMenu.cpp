#include "TetrisMenu.h"



void TetrisMenu::handleClick(const sf::Vector2f& mousePos, sf::Color newColor) {//hueta
    int col = (mousePos.x - originX) / cellSize;//hueta
    int row = (mousePos.y - originY) / cellSize;//hueta
    if (row >= 0 && row < rows && col >= 0 && col < cols) {//hueta
        grid[row][col].color = newColor;//hueta
    }
}                   //hueta

TetrisMenu::TetrisMenu(int rows, int cols, int cellSize, int originX, int originY)
    : rows(rows), cols(cols), cellSize(cellSize), originX(originX), originY(originY) {
    grid.resize(rows, std::vector<CellData>(cols, {0, sf::Color::Black}));
}

// void TetrisMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
//     cell.setFillColor(sf::Color(50, 50, 50));
//     for (int y = 0; y < rows; ++y) {
//         for (int x = 0; x < cols; ++x) {
//             cell.setPosition(sf::Vector2f(originX + x * cellSize, originY + y * cellSize));
//             target.draw(cell, states);
//         }
//     }

    void TetrisMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {//hueta
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));//hueta
        for (int y = 0; y < rows; ++y) {//hueta
            for (int x = 0; x < cols; ++x) {//hueta
                cell.setPosition(sf::Vector2f(originX + x * cellSize, originY + y * cellSize));//hueta
                cell.setFillColor(grid[y][x].color);//hueta
                target.draw(cell, states);//hueta
            }//hueta
        }//hueta
    }//hueta


