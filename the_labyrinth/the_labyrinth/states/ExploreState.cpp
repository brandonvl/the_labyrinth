#include "ExploreState.h"
#include "model\Game.h"


int tempCounter = 0;

void ExploreState::init(Game &game)
{
	_game = &game;
}

void ExploreState::cleanUp()
{
	_game = nullptr;
}

void ExploreState::update()
{
	tempCounter++;

	if (tempCounter > 10)
		_game->stop();
}

void ExploreState::displayInfo()
{

}

void ExploreState::displayOptions()
{

}

void ExploreState::doOption()
{

}