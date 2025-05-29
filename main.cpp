#include <sstream>
#include "Game.h"
#include "TetrisMenu.h"

int main()
{
	Game* game = new Game();
	
	game->run();

	delete game;
	game = nullptr;
}
