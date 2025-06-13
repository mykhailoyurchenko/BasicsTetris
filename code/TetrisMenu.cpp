#include <SFML/Graphics.hpp>
#include "TetrisMenu.h"
#include <iostream>



using namespace sf;

TetrisMenu::TetrisMenu(int cellSize, int originX, int originY, Vector2u winSize)
	: cellSize(cellSize), originX(originX), originY(originY), gameFieldNext(Vector2f(230, 600)) {

	gameFieldNext.setFillColor(Color(0, 0, 0, 0.0));
	gameFieldNext.setPosition({ winSize.x * 0.68f, winSize.y * 0.40f });

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
bool TetrisMenu::isGameOver() const {
	for (int x = 0; x < cols; ++x) {
		if (grid[x][0].isFull) return true;
	}
	return false;
}
void TetrisMenu::spawnTetris() {  
	int number = nextTetrises[0];
    int randomX = number == 0 ? rand() % (cols - 3) : rand() % (cols - 2);  
	currentTetris.fill({});
    currentType = number;  
    currentColor = tetrisColors[number];  
    for (int i = 0; i < 4; i++) {  
        currentTetris[i].x = tetrisShapes[number][i].x + randomX;
		currentTetris[i].y = tetrisShapes[number][i].y;
    }  
    isMoving = true;  
    moveTimer = 0.f;
    if (isGameOver()) {
        isMoving = false;
    }
}
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
			target.draw(cell, states);
		}
	}
	drawNextTetrises(target);
}
void TetrisMenu::drawNextTetrises(RenderTarget& target) const {
	const float cellSize = 42.f;

	RectangleShape block(Vector2f(cellSize, cellSize));
	block.setOutlineColor(Color(29, 29, 29));
	block.setOutlineThickness(-1.f);

	Vector2f startPosition = gameFieldNext.getPosition() + Vector2f(-60.f, -380.f);
	Vector2f verticalOffset(0.f, cellSize * 4.f);

	for (int i = 1; i < 4; ++i) {
		int figureType = nextTetrises[i];
		const auto& shape = tetrisShapes[figureType];

		block.setFillColor(tetrisColors[figureType]);
		for (const auto& cell : shape) {
			block.setPosition(startPosition + verticalOffset * float(i) + Vector2f(cell.x * cellSize, cell.y * cellSize));
			target.draw(block);
		}
	}
	target.draw(gameFieldNext);
}