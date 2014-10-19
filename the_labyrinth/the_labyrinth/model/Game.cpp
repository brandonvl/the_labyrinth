#include "Game.h"
#include "states\GameState.h"
#include "states\ExploreState.h"
#include "Floor.h"


Game::Game()
{
}


Game::~Game()
{
	if (_state != nullptr)
		_state->cleanUp();

	delete _testFloor;
}

void Game::run()
{
	_testFloor = new Floor();
	_testFloor->createFloor(5, 1, 3);
	changeState(ExploreState::instance());
	_running = true;

	while (_running)
	{
		_state->update();
	}
}

void Game::stop()
{
	_running = false;
}

void Game::changeState(GameState &state)
{
	if (_state != nullptr)
		_state->cleanUp();

	_state = &state;

	_state->init(*this);
}