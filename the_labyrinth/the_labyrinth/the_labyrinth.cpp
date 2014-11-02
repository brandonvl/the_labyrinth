
#include "model\Game.h"
#include <iostream>

#include "vld\include\vld.h"

int main()
{
	Game *game = new Game();
	game->run();
	delete game;
}