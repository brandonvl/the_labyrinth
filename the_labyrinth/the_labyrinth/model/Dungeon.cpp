#include "Dungeon.h"
#include "Floor.h"
#include "Chamber.h"
#include "model\enums.h"
#include "model\Monster.h"
#include "util\FileManager.h"

#include <iostream>

Dungeon::Dungeon()
{
	_floors.reserve(5);
	_currentFloor = nullptr;
}


Dungeon::~Dungeon()
{
	for (auto it : _floors)
	{
		delete it;
		it = nullptr;
	}
}

void Dungeon::createDungeon()
{
	Floor *previousFloor = nullptr;

	int maxLevel = 10;
	int minLevel = 1;
	int lastLevelMaxLevel = minLevel;
	int increment = floor(maxLevel / _floors.capacity());

	for (unsigned int i = 0; i < _floors.capacity(); i++)
	{
		Floor *floor = new Floor();
		if ((lastLevelMaxLevel + increment) > maxLevel)
			floor->createFloor(10, lastLevelMaxLevel, maxLevel);
		else
			floor->createFloor(10, lastLevelMaxLevel, lastLevelMaxLevel + increment);

		lastLevelMaxLevel += increment;
		_floors.push_back(floor);

		if (previousFloor != nullptr) {
			previousFloor->getEnd().addNeighbour(Direction::UPSTAIRS, floor->getStart());
			floor->getStart().addNeighbour(Direction::DOWNSTAIRS, previousFloor->getEnd());
		}

		previousFloor = floor;
	}

	_currentFloor = *_floors.begin();
	//_currentFloor = *(_floors.end() - 1);
	_start = &(*_floors.begin())->getStart();
	_end = &(*(_floors.end()-1))->getEnd();

	_end->clearMonsters();
	Monster *monster = FileManager::getRandomBoss(11, 11);

	_end->addMonster(*monster);
}
