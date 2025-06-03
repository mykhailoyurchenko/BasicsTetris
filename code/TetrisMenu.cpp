#include <TetrisMenu.h>
#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;

TetrisMenu::TetrisMenu(gridType& grid,int cellSize, int originX, int originY)
    : grid(grid), cellSize(cellSize), originX(originX), originY(originY) {
	cols = 10;
	rows = 20;
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			grid[x][y].x = x;
			grid[x][y].y = y;
		}
	}
    for (int i = 0; i < 4;i++)
	{
        tetrises[0][i] = CellData{i, 0, Color::Cyan };
    }
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[1][i] = CellData{ 0, i, Color::Blue };
		else tetrises[1][i] = CellData{ i - 1, 1, Color::Blue };
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 3) tetrises[2][i] = CellData{ i, 1, Color(240,160,0)};
		else tetrises[2][i] = CellData{ 2, 0, Color(240,160,0) };
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[3][i] = CellData{0, i, Color::Yellow };
		else tetrises[3][i] = CellData{1, i - 2, Color::Yellow };
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[4][i] = CellData{i, 1, Color::Green};
		else tetrises[4][i] = CellData{i - 1, 0, Color::Green};
	}
    for (int i = 0; i < 4; i++)
    {
		if (i < 3) tetrises[5][i] = CellData{ i, 1, Color(160,0,240) };
        else tetrises[5][i] = CellData{1, 0,Color(160,0,240) };
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[6][i] = CellData{i, 0, Color::Red};
		else tetrises[6][i] = CellData{i - 1, 1, Color::Red};
	}
}	
void TetrisMenu::drawTetris(int number) {
	srand(time(0));
	int randomX = rand() % (cols-2);
	for(auto& tetris : tetrises[number]) {
		int x = tetris.x + randomX;
		int y = tetris.y;
		if (x >= 0 && x < cols && y >= 0 && y < rows) {
			grid[x][y].color = tetris.color;
		}
	}
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