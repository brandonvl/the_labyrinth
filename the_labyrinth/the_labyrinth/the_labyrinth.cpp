
#include "model\Game.h"
#include <iostream>

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	Game *game = new Game();
	game->run();
	std::cin.get();
	delete game;
	_CrtDumpMemoryLeaks();
}