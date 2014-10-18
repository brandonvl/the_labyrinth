#include "GameState.h"
#include "model\Game.h"

void GameState::displayInfo()
{
	std::cout << "Displayinfo not implemented." << std::endl;
}

void GameState::displayOptions()
{
	std::cout << "DisplayOptions not implemented. " << std::endl;
}

void GameState::doOption()
{
	std::cout << "DoOption not implemented. " << std::endl;
}

void GameState::changeState(GameState &state)
{
	_game->changeState(state);
}

