#include <TetrisMenu.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

TetrisMenu::TetrisMenu(gridType& grid, int cellSize, int originX, int originY)
    : grid(grid), cellSize(cellSize), originX(originX), originY(originY)  {
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
    // ...ініціалізація tetrisShapes як раніше...
    tetrisShapes = { {
            // I
            {{{0,0}, {1,0}, {2,0}, {3,0}}},
            // J
            {{{0,0}, {0,1}, {1,1}, {2,1}}},
            // L
            {{{2,0}, {0,1}, {1,1}, {2,1}}},
            // O
            {{{0,0}, {1,0}, {0,1}, {1,1}}},
            // S
            {{{1,0}, {2,0}, {0,1}, {1,1}}},
            // T
            {{{1,0}, {0,1}, {1,1}, {2,1}}},
            // Z
            {{{0,0}, {1,0}, {1,1}, {2,1}}}
        } };
}
void TetrisMenu::spawnTetris(int number) {
    int randomX = number == 0 ? rand() % (cols - 3) : rand() % (cols - 2);
    clearTopRows();
    currentTetris.clear();
    currentType = number;
    currentColor = tetrisColors[number];
    for (int i = 0; i < 4; i++) {
        int x = tetrisShapes[number][i].first + randomX; // стартова позиція по центру
        int y = tetrisShapes[number][i].second;
        currentTetris.push_back({ x, y });
    }
    isMoving = true;
    moveTimer = 0.f;
}
//std::cout << ": " << number << "X " << tetris.x << std::endl;
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
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < 2; y++) {
            grid[x][y].color = Color::Black;
            grid[x][y].isFull = false;
        }
    }
}
// Повороти фігур
void TetrisMenu::rotateTetris() {
    if (currentType == 3) return; // O-фігура не обертається

    sf::Vector2i pivot = currentTetris[1];
    std::vector<sf::Vector2i> rotated;
    for (const auto& block : currentTetris) {
        int x = block.x - pivot.x;
        int y = block.y - pivot.y;
        rotated.push_back({ pivot.x - y, pivot.y + x });
    }

    auto fits = [&](const std::vector<sf::Vector2i>& shape) {
        for (const auto& block : shape) {
            if (block.x < 0 || block.x >= cols || block.y < 0 || block.y >= rows)
                return false;
            if (grid[block.x][block.y].isFull)
                return false;
        }
        return true;
        };

    // ⚠️ Додаткова перевірка для I-фігури:
    if (currentType == 0) {
        // Перевірити, чи поточна фігура у вертикальному положенні
        bool isVertical = true;
        int x0 = currentTetris[0].x;
        for (const auto& block : currentTetris) {
            if (block.x != x0) {
                isVertical = false;
                break;
            }
        }

        // Якщо вертикальна і близько до меж, не дозволяємо обертання
        if (isVertical) {
            for (const auto& block : currentTetris) {
                if (block.x <= 1 || block.x >= cols - 2) {
                    return; // Близько до краю в вертикальному вигляді
                }
            }
        }
    }

    if (fits(rotated)) {
        currentTetris = rotated;
        return;
    }

    // Wall kicks
    std::vector<sf::Vector2i> shifts;
    if (currentType == 0) {
        shifts = {
            {-2, 0}, {-1, 0}, {1, 0}, {2, 0},
            {0, -1}, {0, -2}, {0, 1}, {0, 2},
            {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
        };
    }
    else {
        shifts = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
        };
    }

    for (const auto& shift : shifts) {
        std::vector<sf::Vector2i> kicked;
        for (const auto& block : rotated) {
            kicked.push_back({ block.x + shift.x, block.y + shift.y });
        }
        if (fits(kicked)) {
            currentTetris = kicked;
            return;
        }
    }
}



// перевірка на натискання 
void TetrisMenu::handleRotationInput() {
    bool rotateNow = Keyboard::isKeyPressed(Keyboard::Key::W);

    if (rotateNow && !rotatePressedLastFrame) {
        rotateTetris();
        rotatePressedLastFrame = true;
    }

    if (!rotateNow) {
        rotatePressedLastFrame = false;
    }
}
void TetrisMenu::leftMove() {
    if (canMove(-1, 0)) {
        for (auto& block : currentTetris) block.x -= 1;
        autoRotated = false;
    }
    else if (!autoRotated) {

        rotateTetris();

        if (canMove(-1, 0)) {
            for (auto& block : currentTetris) block.x -= 1;
        }
        autoRotated = true;
    }
    updateCurrentTetris();
}

void TetrisMenu::rightMove() {
    if (canMove(1, 0)) {
        for (auto& block : currentTetris) block.x += 1;
        autoRotated = false;
    }
    else if (!autoRotated) {

        rotateTetris();

        if (canMove(1, 0)) {
            for (auto& block : currentTetris) block.x += 1;
        }
        autoRotated = true;
    }
    updateCurrentTetris();
}

void TetrisMenu::update(float delta) {
    if (!isMoving) return;
    handleRotationInput();
    moveTimer += delta;
    if (moveTimer >= moveInterval) {
        moveTimer = 0.f;
        if (canMove(0, 1)) {
            for (auto& block : currentTetris) block.y += 1;
            autoRotated = false;
        }
        else {
            lockTetris();
        }
    }
    updateCurrentTetris();
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
            target.draw(cell);
        }
    }
}
