
#include "model\Game.h"
#include <iostream>

#ifdef _DEBUG
#include "vld\include\vld.h"
#endif

int main()
{
	Game *game = new Game();
	game->run();
	delete game;
}