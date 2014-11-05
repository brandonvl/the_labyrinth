#include "FightState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "model\Monster.h"
#include "model\Chamber.h"
#include <vector>


void FightState::init(Game &game)
{
	_game = &game;
	_player = &game.getPlayer();
	_monsters = game.getPlayer().getCurrentRoom()->getMonsters();
	system("cls");
}

void FightState::cleanUp()
{
	_game = nullptr;
}

void FightState::update()
{

}

void FightState::displayInfo()
{

}

void FightState::displayOptions()
{

}

void FightState::doOption()
{

}