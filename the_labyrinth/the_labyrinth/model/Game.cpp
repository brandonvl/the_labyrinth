#include "Game.h"
#include "states\GameState.h"
#include "states\ExploreState.h"
#include "Dungeon.h"


Game::Game()
{
}


Game::~Game()
{
	if (_state != nullptr)
		_state->cleanUp();

	delete _dungeon;
}

void Game::run()
{
	_dungeon = new Dungeon();
	_dungeon->createDungeon();
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