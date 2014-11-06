#include "FightState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "model\Monster.h"
#include "model\Chamber.h"
#include <vector>
#include "util\RandomGenerator.h"


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
	std::cout << "You have " << _player->getHealth() << " out of " << _player->getMaxHealth() << " HP remaining." << std::endl << std::endl;
}

void FightState::doMonsterActions()
{
	std::cout << "Monster actions: " << std::endl;
	int damage;
	std::string writeString = "";
	for (Monster *monster : *_monsters)
	{
		if (_player->getHealth() > 0) {
			damage = doCombat(*monster, *_player);
			writeString = monster->getName() + " ( " + std::to_string(monster->getLevel()) + " ) attacks and ";
			if (damage == -1)
				writeString.append("misses");
			else
				writeString.append("deals " + std::to_string(damage) + " damage.");

			std::cout << writeString << std::endl;
		}
	}

	std::cout << std::endl;
}

void FightState::update()
{
	doDisplayMonsterInfo();
	if (_userInitiated)
	{
		doDisplayPlayerStatus();
		displayOptions();
		doOption();

		_userInitiated = false;
	}
	else
	{
		doMonsterActions();
		doDisplayPlayerStatus();
		if (_player->getHealth() <= 0) {
			std::cout << "You have died.. Press any key to continue." << std::endl;
			std::cin.get();
			// changeState(GameOverState::instance());
		}
		else
		{
			displayOptions();
			doOption();
		}
		
	}
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
	std::cout << "Options: [|fight|flee|inventory]" << std::endl;
	std::cout << "Your choice: ";
	std::getline(std::cin, _chosenOption);
	std::cout << std::endl;
}

int FightState::doCombat(Creature &attacker, Creature &defender)
{
	int attackRoll = RandomGenerator::random(0, attacker.getAttack());
	int defenseRoll = RandomGenerator::random(0, defender.getDefense());

	if (attackRoll > defenseRoll)
	{
		// do Attack
		defender.addHealth(-defender.getAttackValue());
		return defender.getAttackValue();
	}
	else
		return -1;
}

void FightState::doOption()
{

}