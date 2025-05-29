//
// Created by STALJ on 24.05.2025.
//

#ifndef TETRISMENU_H
#define TETRISMENU_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


struct CellData {
    int value;           // e.g., block type or 0 for empty
    sf::Color color;     // color of the cell
    // add more fields as needed
};

class TetrisMenu : public sf::Drawable {
public:
    TetrisMenu(int rows, int cols, int cellSize, int originX, int originY);

    void handleClick(const sf::Vector2f& mousePos, sf::Color newColor = sf::Color::Red);//hueta
    // Draws the grid
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    int rows, cols, cellSize, originX, originY;
    std::vector<std::vector<CellData>> grid;
};


#endif //TETRISMENU_H
