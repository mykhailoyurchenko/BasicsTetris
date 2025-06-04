#include <TetrisMenu.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

TetrisMenu::TetrisMenu(gridType& grid, int cellSize, int originX, int originY)
    : grid(grid), cellSize(cellSize), originX(originX), originY(originY) {
    cols = 10;
    rows = 20;
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            grid[x][y].x = x;
            grid[x][y].y = y;
            grid[x][y].color = Color::Black;
            grid[x][y].isFull = false;
        }
    }
    // ...ініціалізація tetrises як раніше...
    for (int i = 0; i < 4; i++) tetrises[0][i] = CellData{i, 0, Color::Cyan };
    for (int i = 0; i < 4; i++) {
        if (i < 2) tetrises[1][i] = CellData{ 0, i, Color::Blue };
        else tetrises[1][i] = CellData{ i - 1, 1, Color::Blue };
    }
    for (int i = 0; i < 4; i++) {
        if (i < 3) tetrises[2][i] = CellData{ i, 1, Color(240,160,0)};
        else tetrises[2][i] = CellData{ 2, 0, Color(240,160,0) };
    }
    for (int i = 0; i < 4; i++) {
        if (i < 2) tetrises[3][i] = CellData{0, i, Color::Yellow };
        else tetrises[3][i] = CellData{1, i - 2, Color::Yellow };
    }
    for (int i = 0; i < 4; i++) {
        if (i < 2) tetrises[4][i] = CellData{i, 1, Color::Green};
        else tetrises[4][i] = CellData{i - 1, 0, Color::Green};
    }
    for (int i = 0; i < 4; i++) {
        if (i < 3) tetrises[5][i] = CellData{ i, 1, Color(160,0,240) };
        else tetrises[5][i] = CellData{1, 0,Color(160,0,240) };
    }
    for (int i = 0; i < 4; i++) {
        if (i < 2) tetrises[6][i] = CellData{i, 0, Color::Red};
        else tetrises[6][i] = CellData{i - 1, 1, Color::Red};
    }
}

void TetrisMenu::spawnTetris(int number) {
    int randomX = number == 0 ? rand() % (cols - 3) : rand() % (cols - 2);
    clearTopRows();
    currentTetris.clear();
    currentType = number;
    currentColor = tetrises[number][0].color;
    for (int i = 0; i < 4; i++) {
        int x = tetrises[number][i].x + randomX; // стартова позиція по центру
        int y = tetrises[number][i].y;
        currentTetris.push_back({x, y});
    }
    isMoving = true;
    moveTimer = 0.f;
}
// void TetrisMenu::drawTetris(int number) {
// 	srand(time(0));
	
	
// 	for(auto& tetris : tetrises[number]) {
		
// 		int x = tetris.x + randomX;
// 		int y = tetris.y;
		
		
// 		if (x >= 0 && x < cols && y >= 0 && y < rows) {
// 			grid[x][y].color = tetris.color;
// 		}
// 		//std::cout << ": " << number << "X " << tetris.x << std::endl;
// 	}

bool TetrisMenu::canMove(int dx, int dy) const {
    for (const auto& block : currentTetris) {
        int nx = block.x + dx;
        int ny = block.y + dy;
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) return false;
        if (grid[nx][ny].isFull) return false;
    }
    return true;
}

void TetrisMenu::lockTetris() {
    for (const auto& block : currentTetris) {
        int x = block.x;
        int y = block.y;
        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            grid[x][y].color = currentColor;
            grid[x][y].isFull = true;
        }
    }
    isMoving = false;
}

void TetrisMenu::clearTopRows() {
    for (int x = 0; x < cols; ++x) {
        for (int y = 0; y < 2; ++y) {
            grid[x][y].color = Color::Black;
            grid[x][y].isFull = false;
        }
    }
}
void TetrisMenu::handleHorizontalInput() {
    bool leftNow = Keyboard::isKeyPressed(Keyboard::Key::A);
    bool rightNow = Keyboard::isKeyPressed(Keyboard::Key::D);

    if (leftNow && !leftPressedLastFrame) {
        if (canMove(-1, 0)) {
            for (auto& block : currentTetris) block.x -= 1;
        }
    }

    if (rightNow && !rightPressedLastFrame) {
        if (canMove(1, 0)) {
            for (auto& block : currentTetris) block.x += 1;
        }
    }

    

    for (int x = 0; x < cols; ++x)
        for (int y = 0; y < rows; ++y)
            if (!grid[x][y].isFull)
                grid[x][y].color = Color::Black;
    if (isMoving) {
        for (const auto& block : currentTetris) {
            int x = block.x, y = block.y;
            if (x >= 0 && x < cols && y >= 0 && y < rows)
                grid[x][y].color = currentColor;
        }
    }

}

void TetrisMenu::update(float delta) {
    if (!isMoving) return;
    moveTimer += delta;
    if (moveTimer >= moveInterval) {
        moveTimer = 0.f;
        if (canMove(0, 1)) {
            for (auto& block : currentTetris) block.y += 1;
        } else {
            lockTetris();
        }
    }
    
    // Оновити grid для відображення поточної фігури
    for (int x = 0; x < cols; ++x)
        for (int y = 0; y < rows; ++y)
            if (!grid[x][y].isFull)
                grid[x][y].color = Color::Black;
    if (isMoving) {
        for (const auto& block : currentTetris) {
            int x = block.x, y = block.y;
            if (x >= 0 && x < cols && y >= 0 && y < rows)
                grid[x][y].color = currentColor;
        }
    }
}


bool TetrisMenu::isActive() const {
    return isMoving;
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
