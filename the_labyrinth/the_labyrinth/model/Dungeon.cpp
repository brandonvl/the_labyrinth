#include "Dungeon.h"
#include "Floor.h"
#include "Chamber.h"
#include "model\enums.h"

// For testing only!
#include "Monster.h"

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
	
	// For testing only
	Monster *monster = new Monster();
	monster->setName("Kevin");
	monster->setAttack(2);
	monster->setDefense(1);
	monster->setPerception(10);
	monster->setMaxHealth(20, true);
	monster->setLevel(1);
	monster->setBaseExperience(50);
	_start->addMonster(*monster);

	Monster *monster2 = new Monster();
	monster2->setName("Kevin");
	monster2->setAttack(2);
	monster2->setDefense(1);
	monster2->setPerception(10);
	monster2->setMaxHealth(20, true);
	monster2->setLevel(1);
	monster2->setBaseExperience(50);
	_start->addMonster(*monster2);

	Monster *monster3 = new Monster();
	monster3->setName("Wouter");
	monster3->setAttack(2);
	monster3->setDefense(1);
	monster3->setPerception(10);
	monster3->setMaxHealth(20, true);
	monster3->setLevel(1);
	monster3->setBaseExperience(50);
	_start->addMonster(*monster3);
}
