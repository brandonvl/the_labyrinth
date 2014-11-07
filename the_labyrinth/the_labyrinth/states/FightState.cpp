#include "FightState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "model\Monster.h"
#include "model\Chamber.h"
#include "model\Dungeon.h"
#include "model\Trap.h"
#include <vector>
#include "util\RandomGenerator.h"
#include "GameOverState.h"
#include "ExploreState.h"
#include "InventoryState.h"


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
	_hasFled = false;
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
	for (unsigned int i = 0; i < _monsters->size(); i++)
	{
		Monster *monster = (*_monsters)[i];
		if (_player->getHealth() > 0 && monster->getHealth() > 0) {
			damage = doCombat(*monster, *_player);
			writeString = std::to_string(i + 1) + ". " + monster->getName() + " ( " + std::to_string(monster->getLevel()) + " ) attacks and ";
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
	system("cls");
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
			changeState(GameOverState::instance());
		}
		else
		{
			displayOptions();
			doOption();
		}
	}

	doCheckMonsterHealth();
}

void FightState::doCheckMonsterHealth()
{
	if (!_hasFled) {

		int deathCounter = 0;
		int experienceGain = 0;
		for (auto it : *_monsters) {
			if (it->getHealth() == 0) {
				deathCounter++;
				experienceGain += it->getExperienceValue();
			}
		}

		if (deathCounter == _monsters->size()) {
			std::cout << "You have gained " << experienceGain << " exp." << std::endl;
			Player &player = _game->getPlayer();
			player.getCurrentRoom()->clearMonsters();
			player.addExperience(experienceGain);

			if (player.isLevelUp()) {
				std::cout << "You have leveled up from " << player.getLevel() << " to " << player.getLevel() + 1 << "." << std::endl;
				std::cout << "Your stats have increased.";
			}

			std::cout << "Press any key to continue..";
			std::cin.get();
			changeState(ExploreState::instance());
		}
	}
	else
	{
		for (auto it : *_monsters)
		{
			it->setMaxHealth(it->getMaxHealth(), true);
		}
	}
}

void FightState::doDisplayMonsterInfo()
{
	std::cout << "Monster info: " << std::endl;
	for(unsigned int i = 0; i < _monsters->size(); i++) {
		Monster *monster = (*_monsters)[i];
		std::cout << std::to_string(i + 1) << ". " << monster->getName() << " ( " << monster->getLevel() << " ): has " << monster->getHealth() << " HP left." << std::endl;
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
		defender.addHealth(-attacker.getAttackValue());
		return attacker.getAttackValue();
	}
	else
		return -1;
}

void FightState::doOption()
{
	if (_chosenOption == "fight") {
		doOptionFight();
	}
	else if (_chosenOption == "flee") {
		doOptionFlee();
	}
	else if (_chosenOption == "inventory") {
		doOptionInventory();
	}
	else
	{
		std::cout << "Invalid choice. Your lost a turn!" << std::endl;
	}
}

void FightState::doOptionFight()
{
	bool didFight = false;
	std::string userInput = "";
	unsigned int monsterSlot;
	size_t monsterSize = _monsters->size();

	do
	{
		std::cout << "Attack monster: ";
		std::getline(std::cin, userInput);

		try
		{
			monsterSlot = std::stoi(userInput);

			if (monsterSize < monsterSlot || monsterSlot < 1)
				std::cout << "Invalid monster slot. Pick a monster slot number (the number before their names)." << std::endl;
			else
			{
				int damage = -1;
				damage = doCombat(*_player, *(*_monsters)[monsterSlot - 1]);
				std::string combatStr = "You attack and ";
				if (damage == -1)
					combatStr.append("miss your target.");
				else
					combatStr.append("deal " + std::to_string(damage) + " to the " + (*_monsters)[monsterSlot - 1]->getName());

				std::cout << combatStr << std::endl;
				std::cout << "Press any key to continue...";
				std::cin.get();
				didFight = true;
			}
				
		}
		catch (std::invalid_argument) {
			std::cout << "Invalid monster slot. Pick a monster slot number (the number before their names)." << std::endl;
		}
		catch (std::out_of_range) {
			std::cout << "Invalid monster slot. Pick a monster slot number (the number before their names)." << std::endl;
		}
		
	} while (!didFight);
}

void FightState::doOptionFlee()
{
	Chamber *randomNeighbour = _player->getCurrentRoom()->getRandomNeighbour();

	if (randomNeighbour == nullptr)
		std::cout << "Unable to flee!" << std::endl;
	else
	{
		const Direction &direction = _player->getCurrentRoom()->getNeighBourDirection(*randomNeighbour);
		if (direction == Direction::INVALID)
		{
			std::cout << "Unable to flee!" << std::endl;
		}
		else
		{
			Trap *trap = _player->getCurrentRoom()->getTrap();

			if (trap != nullptr && !trap->isDismantled()) {
				std::cout << "While you were trying to flee, you have sprung a " << trap->getName() << " that dealt " << trap->getDamage() << " damage." << std::endl;
				trap->doEffect(*_player);

				if (_player->getHealth() == 0)
				{
					std::cout << "You have died... Press any key to continue" << std::endl;
					std::cin.get();
					changeState(GameOverState::instance());
					return;
				}
			}

			if (direction == Direction::UPSTAIRS)
				_game->getDungeon().setNextFloor();
			else if (direction == Direction::DOWNSTAIRS)
				_game->getDungeon().setPreviousFloor();

			std::cout << "You have successfully fled " << directionNames.find(direction)->second << std::endl;

			_hasFled = true;
			randomNeighbour->enter(*_player);
			changeState(ExploreState::instance());
		}
	}

	std::cout << "Press any key to continue..." << std::endl;
	std::cin.get();
}

void FightState::doOptionInventory()
{
	changeState(InventoryState::instance());
}