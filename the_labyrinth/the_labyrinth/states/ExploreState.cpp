#include "ExploreState.h"
#include "InventoryState.h"
#include "model\Game.h"
#include "model\Dungeon.h"
#include "model\Floor.h"
#include "model\Chamber.h"
#include "model\Player.h"
#include "util\ChamberDescriptionBuilder.h"
#include "FightState.h"
#include "model\Monster.h"
#include "model\Trap.h"
#include "states\GameOverState.h"
#include "util\RandomGenerator.h"
#include "util\FileManager.h"
#include "model\Inventory.h"

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
	system("cls");
	displayInfo();
	displayOptions();
	doOption();
}

std::vector<std::string> getNeighBourStrings(Chamber &chamber)
{
	std::vector<std::string> neighbours;

	for (auto it : directionNames)
	{
		if (chamber.hasNeighbour(it.first)) {
			neighbours.push_back(it.second);
		}
	}

	return neighbours;
}

std::string getNeighBourString(Chamber &chamber)
{
	std::vector<std::string> neighbours = getNeighBourStrings(chamber);
	std::string neighOption = "[";
	for (auto it : neighbours) {
		neighOption += "|" + it;
	}

	neighOption += "]";

	return neighOption;
}

std::string getMonsterString(Chamber &chamber)
{
	if (chamber.getMonsters()->size() > 0)
	{
		std::string monsterString;
		std::unordered_map<std::string, int> _tempMonsterMap;

		std::vector<Monster*> *monsters = chamber.getMonsters();

		for (Monster *monster : *monsters)
		{
			if (_tempMonsterMap.find(monster->getName()) != _tempMonsterMap.end()) {
				_tempMonsterMap[monster->getName()]++;
			}
			else
			{
				_tempMonsterMap.insert(std::make_pair(monster->getName(), 1));
			}
		}

		for (auto keyValue : _tempMonsterMap) {
			monsterString.append(std::to_string(keyValue.second) + " " + keyValue.first + " ");
		}

		return monsterString;
	}
	else
	{
		return "none";
	}
}

void ExploreState::displayInfo()
{
	Chamber &chamber = *_game->getPlayer().getCurrentRoom();
	if (TEST_MODE && chamber.getTrap() != nullptr)
		std::cout << "HAS TRAP";
	std::cout << "Description: " << ChamberDescriptionBuilder::getDescription(chamber) << std::endl << std::endl;
	std::cout << "Exits: " << getNeighBourString(chamber) << std::endl << std::endl;
	std::cout << "Monsters: " << getMonsterString(chamber);
	std::cout << std::endl << std::endl;
}



void ExploreState::displayOptions()
{
	std::string optionString = "[";

	Player &player = _game->getPlayer();
	Chamber *chamber = player.getCurrentRoom();

	if (chamber->getMonsters()->size() > 0) {
		optionString += "|fight";
	}
	else
		optionString += "|rest";

	optionString += "|move|map|inventory|status";

	if (!chamber->isExplored())
		optionString += "|explore";

	optionString += "|quit]";

	std::cout << "Options: " << optionString << std::endl << std::endl;
	std::cout << "You choose: ";
	std::getline(std::cin, _chosenOption);
	std::cout << std::endl;
}

void ExploreState::doOption()
{
	if (_chosenOption == "fight" && _game->getPlayer().getCurrentRoom()->getMonsters()->size() > 0) {
		doOptionFight();
		_chosenOption = "";
		return;
	}
	else if (_chosenOption == "rest" && _game->getPlayer().getCurrentRoom()->getMonsters()->size() == 0)
	{
		doOptionRest();
	}
	else if (_chosenOption == "explore" && !_game->getPlayer().getCurrentRoom()->isExplored())
	{
		doOptionExplore();
	}
	else if (_chosenOption == "move")
	{
		Player &player = _game->getPlayer();
		Chamber *chamber = player.getCurrentRoom();
		doOptionMove(player, *chamber);
	}
	else if (_chosenOption == "map")
	{
		doOptionShowMap();
	}
	else if (_chosenOption == "status")
	{
		doOptionShowStatus(_game->getPlayer());
	}
	else if (_chosenOption == "inventory")
	{
		doOptionShowInventory();
	}
	else if (_chosenOption == "quit") {
		doOptionQuit();
	}
	else
	{
		std::cout << "Invalid choice, you have lost a turn." << std::endl;
		std::cout << "Press any key to continue...";
		std::cin.get();
	}

	std::cout << std::endl;
	_chosenOption = "";
}

void ExploreState::doOptionRest()
{
	int enemyEncounter = RandomGenerator::random(0, 100);
	Player &player = _game->getPlayer();
	player.addHealth(5);
	std::cout << "You have regained some health while resting." << std::endl;

	if (enemyEncounter < 30) {
		
		int minLevel = player.getLevel() > 2 ? player.getLevel() - 2 : 1;
		int maxLevel = player.getLevel();
		Monster *monster = FileManager::getRandomMonster(minLevel, maxLevel);
		player.getCurrentRoom()->addMonster(*monster);
		std::cout << "While you were resting a level " << monster->getLevel() << " " << monster->getName() << " has entered the room!" << std::endl;
	}

	std::cout << "Press any key to continue...";
	std::cin.get();
}

void ExploreState::doOptionShowStatus(Player &player)
{
	std::cout << "==== Status of " << player.getName() << " ====" << std::endl;
	std::cout << "Level: " << player.getLevel() << std::endl;
	std::cout << "HP / MaxHP: " << player.getHealth() << " / " << player.getMaxHealth() << std::endl;
	std::cout << "AttackValue: " << player.getAttackValue() << std::endl;
	std::cout << "Defense: " << player.getDefense() << std::endl;
	std::cout << "Attack: " << player.getAttack() << std::endl;
	std::cout << "Perception: " << player.getPerception() << std::endl;
	std::cout << "Press any key to continue...";
	std::cin.get();
	std::cout << std::endl;
	
}

void ExploreState::doOptionMove(Player &player, Chamber &chamber)
{
	std::string neighOption = getNeighBourString(chamber);
	std::cout << neighOption << std::endl;
	std::cout << "Move where: ";
	std::getline(std::cin, _chosenOption);
	Direction direction = Direction::INVALID;
	for (auto it : directionNames) {
		if (it.second == _chosenOption) {
			direction = it.first;
			break;
		}
	}

	if (chamber.hasNeighbour(direction)) {

		Trap *trap = chamber.getTrap();

		if (trap != nullptr && !trap->isDismantled()) {
			std::cout << "While you were moving, you have sprung a " << trap->getName() << " that dealt " << trap->getDamage() << " damage." << std::endl;
			trap->doEffect(player);

			if (player.getHealth() == 0)
			{
				std::cout << "You have died... Press any key to continue" << std::endl;
				std::cin.get();
				changeState(GameOverState::instance());
				return;
			}
			std::cout << "Press any key to continue" << std::endl;
			std::cin.get();
		}

		if (direction == Direction::UPSTAIRS)
			_game->getDungeon().setNextFloor();
		else if (direction == Direction::DOWNSTAIRS)
			_game->getDungeon().setPreviousFloor();

		chamber.getNeighbour(direction)->enter(player);
	}
	else
	{
		std::cout << "Invalid choice, you have lost a turn." << std::endl;
		std::cout << "Press any key to continue...";
		std::cin.get();
	}

}

void ExploreState::doOptionFight()
{
	FightState::instance().setUserInitiated();
	changeState(FightState::instance());
}

void ExploreState::doOptionShowMap()
{
	system("cls");

	Dungeon *dungeon = &_game->getDungeon();
	Floor *currentFloor = _game->getDungeon().getCurrentFloor();

	if (currentFloor != nullptr) {
		std::vector<std::vector<Chamber*>> chambers = currentFloor->getChambers();

		std::cout << "Dungeon map:" << std::endl;
		for (auto row : chambers)
		{
			for (Chamber *cham : row)
			{
				showChamber(cham);
			}
			std::cout << std::endl;

			for (Chamber *cham : row)
			{
				if (cham->hasNeighbour(Direction::SOUTH) && (TEST_MODE || cham->isVisited() || cham->getNeighbour(Direction::SOUTH)->isVisited())) {
					std::cout << "| ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}

		showMapInfo();

		std::cout << "Press any key to continue..." << std::endl;
		std::cin.get();
	}
}

void ExploreState::doOptionShowInventory() {
	changeState(InventoryState::instance());
}

void ExploreState::doOptionExplore()
{
	Player &player = _game->getPlayer();
	Chamber *chamber = player.getCurrentRoom();

	int beforeItemCount = player.getInventory()->getItemCount();

	chamber->explore(player);

	if (player.getInventory()->getItemCount() > beforeItemCount)
		std::cout << "During your search, you acquired new items" << std::endl;
	else
		std::cout << "During your search, you found no items" << std::endl;

	if (chamber->getTrap() != nullptr && chamber->getTrap()->isDismantled())
		std::cout << "While exploring, you found a " << chamber->getTrap()->getName() << " and you dismantled it." << std::endl;

	std::cout << "Press any key to continue..." << std::endl;
	std::cin.get();

}

void ExploreState::showChamber(Chamber *cham)
{
	std::string chamber;

	if (!TEST_MODE && !cham->isVisited()) {
		chamber = ".";
	}
	else
	{
		if (cham == &_game->getDungeon().getDungeonStart()) {
			chamber = "S";
		}
		else if (cham == &_game->getDungeon().getDungeonEnd()) {
			chamber = "E";
		}
		else if (cham->hasNeighbour(Direction::UPSTAIRS)) {
			chamber = "U";
		}
		else if (cham->hasNeighbour(Direction::DOWNSTAIRS)) {
			chamber = "D";
		}
		else {
			chamber = "N";
		}
	}

	if (cham->hasNeighbour(Direction::EAST) && (TEST_MODE || cham->isVisited() || cham->getNeighbour(Direction::EAST)->isVisited())) {
		chamber += "-";
	}
	else
	{
		chamber += " ";
	}

	std::cout << chamber.c_str();
}

void ExploreState::showMapInfo()
{
	std::cout << "==============" << std::endl;
	std::cout << "|- = Passages" << std::endl;
	std::cout << "N  = Normal room" << std::endl;
	std::cout << "S  = Start location dungeon" << std::endl;
	std::cout << "E  = End location dungeon (boss)" << std::endl;
	std::cout << "U  = Move floor up" << std::endl;
	std::cout << "D  = Move floor down" << std::endl;
	std::cout << ".  = Not visited" << std::endl;
}
