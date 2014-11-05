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

	if (!_userInitiated) {
		std::cout << "You have been ambushed and lured into a fight! Fight to survive or flee.";
	}
	else
	{
		std::cout << "You have challenged the monsters. Defeat the monsters or flee.";
	}

	std::cout << std::endl << std::endl;
}

void FightState::cleanUp()
{
	_game = nullptr;
	_userInitiated = false;
}

void FightState::doDisplayPlayerStatus()
{
	std::cout << "You have " << _player->getHealth() << " out of " << _player->getMaxHealth() << " HP remaining." << std::endl;
}

void FightState::update()
{
	doDisplayMonsterInfo();
	if (_userInitiated)
	{
		doDisplayPlayerStatus();
		displayOptions();
		_userInitiated = false;
	}
	else
	{
		doDisplayPlayerStatus();
	}
	std::cin.get();
}

void FightState::doDisplayMonsterInfo()
{
	std::cout << "Monster info: " << std::endl;
	for (Monster *monster : *_monsters) {
		std::cout << monster->getName() << " ( " << monster->getLevel() << " ): has " << monster->getHealth() << " HP left." << std::endl;
	}

	std::cout << std::endl;
}

void FightState::displayInfo()
{

}

void FightState::displayOptions()
{

}

void FightState::doCombat(Creature &attacker, Creature &defender)
{

}

void FightState::doOption()
{

}