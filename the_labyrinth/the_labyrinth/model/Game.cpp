#include "Game.h"
#include "states\GameState.h"
#include "states\ExploreState.h"
#include "states\IntroState.h"
#include "Dungeon.h"
#include "Player.h"
#include "Chamber.h"
#include "util\FileManager.h"

Game::Game()
{
	FileManager::load();
}


Game::~Game()
{
	if (_state != nullptr)
		_state->cleanUp();

	delete _player;
	delete _dungeon;

	FileManager::unload();
}

void Game::run()
{
	//_dungeon = new Dungeon();
	//_player = new Player();
	//_dungeon->createDungeon();
	//_dungeon->getDungeonStart().enter(*_player);
	changeState(IntroState::instance());
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

void Game::createDungeon(Player &player)
{
	_dungeon = new Dungeon();
	_player = &player;
	_dungeon->createDungeon();
	_dungeon->getDungeonStart().enter(*_player);
}

JSON::JSONElement *Game::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);
	return obj;
}