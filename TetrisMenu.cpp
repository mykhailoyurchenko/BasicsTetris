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
    for (int i = 0; i < 4;i++)
	{
        tetrises[0][i] = Vector2f(i, 0);
    }
	for (int i = 0; i < 4; i++)
	{
        if(i < 2) tetrises[1][i] = Vector2f(0, i);
        else tetrises[1][i] = Vector2f(i - 1, 1); 
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 3) tetrises[2][i] = Vector2f(i, 0);
		else tetrises[2][i] = Vector2f(2, -1);
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[3][i] = Vector2f(0, i);
		else tetrises[3][i] = Vector2f(1, i - 2);
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 2) tetrises[4][i] = Vector2f(i, 1);
		else tetrises[4][i] = Vector2f(i - 1, 0);
	}
    for (int i = 0; i < 4; i++)
    {
        if (i < 2) tetrises[5][i] = Vector2f(i, 1);
        else tetrises[5][i] = Vector2f(1, 1);
	}
	for (int i = 0; i < 4; i++)
	{
		if (i < 3) tetrises[6][i] = Vector2f(i, 0);
		else tetrises[6][i] = Vector2f(1, -1);
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


