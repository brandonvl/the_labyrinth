#include "Game.h"
#include "states\GameState.h"
#include "states\ExploreState.h"
#include "Dungeon.h"
#include "Player.h"
#include "Chamber.h"


Game::Game()
{
	
}


Game::~Game()
{
	if (_state != nullptr)
		_state->cleanUp();

	delete _player;
	delete _dungeon;
}

void Game::run()
{
	_dungeon = new Dungeon();
	_dungeon->createDungeon();
	_player = new Player();
	_dungeon->getDungeonStart().enter(*_player);
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