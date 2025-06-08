#include <SFML/Graphics.hpp>
#include "TetrisMenu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace sf;

TetrisMenu::TetrisMenu(int cellSize, int originX, int originY)
	: cellSize(cellSize), originX(originX), originY(originY) {
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
	for (int i = 0; i < nextTetrises.size(); ++i) {
		nextTetrises[i] = rand() % 7;
	}
	// ...ініціалізація tetrisShapes як раніше...
	tetrisShapes = { {
			// I
			{{{0,0}, {2,0}, {1,0}, {3,0}}},
			// J
			{{{0,0}, {0,1}, {1,1}, {2,1}}},
			// L
			{{{2,0}, {0,1}, {1,1}, {2,1}}},
			// O
			{{{0,0}, {1,0}, {0,1}, {1,1}}},
			// S
			{{{1,0}, {2,0}, {1,1}, {0,1}}},
			// T
			{{{1,0}, {0,1}, {1,1}, {2,1}}},
			// Z
			{{{0,0}, {1,0}, {1,1}, {2,1}}}
		} };

}
bool TetrisMenu::canMove(int dx, int dy) const {
	for (const auto& block : currentTetris) {
		int nx = block.x + dx;
		int ny = block.y + dy;
		if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) return false;
		if (grid[nx][ny].isFull) return false;
	}
	return true;
}

void TetrisMenu::clearTopRows() { // Temporary
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < 2; y++) {
			grid[x][y].color = Color::Black;
			grid[x][y].isFull = false;
		}
	}
}
void TetrisMenu::clearFullRows() {
	int linesCleared = 0;
	for (int y = rows - 1; y >= 0; y--) {
		bool full = true;
		for (int x = 0; x < cols; x++) {
			if (!grid[x][y].isFull) {
				full = false;
				break;
			}
		}
		if (full) {
			// Зсуваємо всі рядки вище вниз
			for (int ty = y; ty > 0; ty--) {
				for (int x = 0; x < cols; x++) {
					grid[x][ty] = grid[x][ty - 1];
				}
			}
			// Очищення верхнього рядка
			for (int x = 0; x < cols; ++x) {
				grid[x][0].color = Color::Black;
				grid[x][0].isFull = false;
			}
			y++; // перевіряємо цей рядок ще раз
			linesCleared++;
		}
	}
	if (linesCleared > 0) {
		score += linesCleared * 100;
	}
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
	clearFullRows();
	isMoving = false;
}
void TetrisMenu::spawnTetris() {  
	int number = nextTetrises[0];
    int randomX = number == 0 ? rand() % (cols - 3) : rand() % (cols - 2);  
    clearTopRows();  
	currentTetris.fill({});
    currentType = number;  
    currentColor = tetrisColors[number];  
    for (int i = 0; i < 4; i++) {  
        currentTetris[i].x = tetrisShapes[number][i].x + randomX;// стартова позиція по центру  
		currentTetris[i].y = tetrisShapes[number][i].y;
    }  
    isMoving = true;  
    moveTimer = 0.f;  
}
//std::cout << ": " << number << "X " << tetris.x << std::endl;
// Повороти фігур
void TetrisMenu::rotateTetris() {
	if (currentType == 3) return;

	Vector2i pivot = currentTetris[2];
	std::array<Vector2i,4> rotated;
	for (int i = 0; i < 4; i++) {
		int x = currentTetris[i].x - pivot.x;
		int y = currentTetris[i].y - pivot.y;
		rotated[i] = { pivot.x - y, pivot.y + x };
	}

	auto fits = [&](const std::array<Vector2i,4>& shape) {
		for (const auto& block : shape) {
			if (block.x < 0 || block.x >= cols || block.y < 0 || block.y >= rows)
				return false;
			if (grid[block.x][block.y].isFull)
				return false;
		}
		return true;
		};

	if (fits(rotated)) {
		currentTetris = rotated;
		return;
	}
	// Інакше — спробувати wall kicks (ручна реалізація)
	std::vector<Vector2i> kicks = {
		{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }, // горизонтальні та вертикальні зсуви
		{ -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 }, // діагональні зсуви
		{ -2, 0 }, { 2, 0 } // додаткові широкі зсуви
	};

	for (const auto& shift : kicks) {
		std::array<Vector2i,4> kicked;
		for (int i = 0; i < 4; i++) {
			kicked[i] = { rotated[i].x + shift.x, rotated[i].y + shift.y };
		}
		if (fits(kicked)) {
			currentTetris = kicked;
			return;
		}
	}
}
void TetrisMenu::updateCurrentTetris() {
	// Оновити grid для відображення поточної фігури
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			if (!grid[x][y].isFull) {
				grid[x][y].color = Color::Black;
			}
		}
	}
	if (isMoving) {
		for (const auto& block : currentTetris) {
			int x = block.x, y = block.y;
			if (x >= 0 && x < cols && y >= 0 && y < rows)
				grid[x][y].color = currentColor;
		}
	}
}
void TetrisMenu::leftMove() {
	if (canMove(-1, 0)) {
		for (auto& block : currentTetris) block.x -= 1;
		upHeld = false;
	}
	updateCurrentTetris();
}

void TetrisMenu::rightMove() {
	if (canMove(1, 0)) {
		for (auto& block : currentTetris) block.x += 1;
		upHeld = false;
	}
	updateCurrentTetris();
}

void TetrisMenu::update(float delta) {
    if (!isMoving) return;
    elapsedTime += delta;
    moveTimer += delta;
    if (moveTimer >= moveInterval) {
        moveTimer = 0.f;
        if (canMove(0, 1)) {
            for (auto& block : currentTetris) block.y += 1;
        }
        else {
            lockTetris();
        }
    }
    updateCurrentTetris();
}

void TetrisMenu::tetrisesShift() {
	for (int i = 0; i < nextTetrises.size() - 1; ++i) {
		nextTetrises[i] = nextTetrises[i + 1];
	}
	nextTetrises[nextTetrises.size() - 1] = rand() % 7;
}

void TetrisMenu::draw(RenderTarget& target, RenderStates states) const {
	RectangleShape cell(Vector2f(cellSize, cellSize));
	cell.setOutlineColor(Color(32, 31, 31));
	cell.setOutlineThickness(1.f);
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			cell.setPosition(Vector2f(originX + x * cellSize, originY + y * cellSize));
			cell.setFillColor(grid[x][y].color);
			target.draw(cell);
		}
	}
}