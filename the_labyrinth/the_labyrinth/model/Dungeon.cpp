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

void Dungeon::setNextFloor()
{
	auto floor = std::find(_floors.begin(), _floors.end(), _currentFloor);
	std::advance(floor, 1);
	_currentFloor = *floor;
}

void Dungeon::setPreviousFloor()
{
	auto floor = std::find(_floors.begin(), _floors.end(), _currentFloor);
	std::advance(floor, -1);

	_currentFloor = *floor;
}

Floor *Dungeon::getNextFloor() {
	return _currentFloor + 1;
}

Floor *Dungeon::getPreviousFloor() {
	return _currentFloor - 1;
}

void Dungeon::createDungeon()
{
	Floor *previousFloor = nullptr;

	int maxLevel = 10;
	int minLevel = 1;
	int lastLevelMaxLevel = minLevel;
	int increment = static_cast<int>(floor(maxLevel / _floors.capacity()));

	for (unsigned int i = 0; i < _floors.capacity(); i++)
	{
		Floor *floor = new Floor();
		floor->setDungeon(*this);
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

JSON::JSONElement &Dungeon::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	int curFloorIndex = 0;
	JSON::JSONArray *floorArr = new JSON::JSONArray(obj);
	for (int i = 0; i < _floors.size(); i++) {
		floorArr->push(_floors[i]->serialize());
		if (_floors[i] == _currentFloor) curFloorIndex = i;
	}
	obj->add("floors", *floorArr);
	obj->add("currentFloor", curFloorIndex);

	return *obj;
}

void Dungeon::deserialize(JSON::JSONObject &element) {

	JSON::JSONArray &floorArr = element.getArray("floors");
	for (int i = 0; i < floorArr.size(); i++) {
		Floor *floor = new Floor();
		floor->setDungeon(*this);
		floor->deserialize(floorArr.getObject(i));
		_floors.push_back(floor);
	}
	_currentFloor = _floors[element.getInt("currentFloor")];
	_start = &_floors[0]->getStart();
	_end = &_floors[_floors.size() - 1]->getEnd();
}