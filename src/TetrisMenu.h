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

    void spawnTetris(int number); // Створити нову фігуру
    void update(float delta);     // Оновлення позиції фігури
    bool isActive() const;        // Чи рухається фігура

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    gridType* getGrid() const { return &grid; }

private:
    int cols, rows, cellSize, originX, originY;
    gridType& grid;
    std::array<std::array<CellData, 4>, 7> tetrises;
    std::vector<sf::Vector2i> currentTetris; // Позиції поточної фігури
    sf::Color currentColor;
    int currentType = -1;
    float moveInterval = 1.0f; // Інтервал спуску (сек)
    float moveTimer = 0.f;
    bool moving = false;

    bool canMove(int dx, int dy) const;
    void lockTetris();
    void clearTopRows();
};
