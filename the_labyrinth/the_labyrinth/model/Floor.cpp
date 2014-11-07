#include "Floor.h"
#include "Chamber.h"
#include "util\RandomGenerator.h"
#include "util\FileManager.h"
#include "Dungeon.h"

#include <stack>
#include <random>

struct ChamberEncap
{
	Chamber *chamber;
	int x;
	int y;
};


Floor::Floor()
{
}


Floor::~Floor()
{
	for (auto it : _chambers)
	{
		for (auto jt : it)
		{
			delete jt;
		}
	}

	_start = nullptr;
	_end = nullptr;
}

void Floor::createFloor(const int &size, const int &minLevel, const int &maxLevel)
{
	_chambers = std::vector<std::vector<Chamber*>>(size);

	// rows
	for (auto it = _chambers.begin(); it != _chambers.end(); it++)
	{
		// init column
		*it = std::vector<Chamber*>(size);

		// generate a room for each cell in the column
		for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
		{
			*jt = &generateChamber(minLevel, maxLevel);
		}
	}

	createMaze(size);
}

Chamber &Floor::generateChamber(const int &minLevel, const int &maxLevel)
{
	// create new chamber with random size, state, lightning, inventory and inventory position
	Chamber *chamber = new Chamber(FileManager::getRandomSize(),
		FileManager::getRandomState(), FileManager::getRandomLightning(),
		FileManager::getRandomFurniture(), FileManager::getRandomFurniturePosition());

	// add random number of random monsters
	int numberOfMonsters = RandomGenerator::random(0, 3);
	for (int i = 0; i < numberOfMonsters; i++) {
		Monster *monster = FileManager::getRandomMonster(minLevel, maxLevel);
		if (monster != nullptr) 
			chamber->addMonster(*monster);
	}

	// add random number of random items
	int numberOfItems = RandomGenerator::random(0, 3);
	for (int i = 0; i < numberOfItems; i++) {
		Item *item = FileManager::getRandomItem();
		if (item != nullptr)
			chamber->addItem(*item);
	}

	// 25% chance there's a trap in the chamber
	if (RandomGenerator::random(0, 4) == 1) {
		Trap *trap = FileManager::getRandomTrap();
		if (trap != nullptr)
			chamber->setTrap(*trap);
	}

	chamber->setFloor(*this);

	return *chamber;
}

void Floor::createMaze(const int &size)
{	
	// DFS - Backtrack algo
	std::stack<ChamberEncap> _visitedCells;

	int totalCells = size * size;
	int visitedCells = 1;

	int chosenX = RandomGenerator::random(0, size - 1);
	int chosenY = RandomGenerator::random(0, size - 1);

	ChamberEncap currentCell;
	currentCell.chamber = _chambers[chosenY][chosenX];
	currentCell.x = chosenX;
	currentCell.y = chosenY;

	while (visitedCells < totalCells)
	{
		std::vector<ChamberEncap> suitableChambers = std::vector<ChamberEncap>();
		
		findSuitableChamber(size, currentCell.x, currentCell.y, suitableChambers);
		

		if (suitableChambers.size() > 0)
		{
			int index = RandomGenerator::random(0, suitableChambers.size() - 1);
			ChamberEncap suitableChamber = suitableChambers[index];
			connectChambers(currentCell, suitableChamber);
			_visitedCells.push(currentCell);
			currentCell = suitableChamber;
			visitedCells++;
		}
		else
		{
			currentCell = _visitedCells.top();
			_visitedCells.pop();
		}

		suitableChambers.clear();
	}

	// select starting point
	int startchosenX = RandomGenerator::random(0, size - 1);
	int startchosenY = RandomGenerator::random(0, size - 1);

	_start = _chambers[startchosenY][startchosenX];

	do
	{
		chosenX = RandomGenerator::random(0, size - 1);
		chosenY = RandomGenerator::random(0, size - 1);
	} while (chosenX == startchosenX && chosenY == startchosenY);

 	_end = _chambers[chosenY][chosenX];
}

void Floor::findSuitableChamber(const int &size, const int &x, const int &y, std::vector<ChamberEncap> &suitableChambers) 
{
	if (x > 0) {
		// check left
		checkChamberValid(x - 1, y, suitableChambers);
	}

	if (x < (size - 1)) {
		// check right
		checkChamberValid(x + 1, y, suitableChambers);
	}

	if (y > 0) {
		// check top
		checkChamberValid(x, y - 1, suitableChambers);
	}

	if (y < (size - 1)) {
		// check down
		checkChamberValid(x, y + 1, suitableChambers);
	}
}

void Floor::checkChamberValid(const int &x, const int &y, std::vector<ChamberEncap> &suitableChambers)
{
	if (_chambers[y][x]->getNeighbourCount() == 0) {
		ChamberEncap cham;
		cham.chamber = _chambers[y][x];
		cham.x = x;
		cham.y = y;
		suitableChambers.push_back(cham);
	}
}

void Floor::connectChambers(ChamberEncap &chamberOne, ChamberEncap &chamberTwo)
{
	if (chamberOne.x == chamberTwo.x) 
	{
		Direction directionChamber1 = chamberOne.y > chamberTwo.y ? Direction::NORTH : Direction::SOUTH;
		Direction directionChamber2 = chamberOne.y > chamberTwo.y ? Direction::SOUTH : Direction::NORTH;
		chamberOne.chamber->addNeighbour(directionChamber1, *chamberTwo.chamber);
		chamberTwo.chamber->addNeighbour(directionChamber2, *chamberOne.chamber);
	}
	else
	{
		Direction directionChamber1 = chamberOne.x > chamberTwo.x ? Direction::WEST : Direction::EAST;
		Direction directionChamber2 = chamberOne.x > chamberTwo.x ? Direction::EAST : Direction::WEST;
		chamberOne.chamber->addNeighbour(directionChamber1, *chamberTwo.chamber);
		chamberTwo.chamber->addNeighbour(directionChamber2, *chamberOne.chamber);
	}
}

void Floor::findChamberPosition(Chamber &chamber, int &outX, int &outY) {
	for (int y = 0; y < _chambers.size(); y++) {
		for (int x = 0; x < _chambers[y].size(); x++) {
			if (_chambers[y][x] == &chamber) {
				outX = x;
				outY = y;
				return;
			}
		}
	}
	outX = -1;
	outY = -1;
}

JSON::JSONElement &Floor::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	int startX = 0, startY = 0, endX = 0, endY = 0;

	JSON::JSONArray *chamberArr = new JSON::JSONArray(obj);
	for (int y = 0; y < _chambers.size(); y++) {
		JSON::JSONArray *subArr = new JSON::JSONArray(chamberArr);
		for (int x = 0; x < _chambers[y].size(); x++) {
			subArr->push(_chambers[y][x]->serialize());

			if (_chambers[y][x] == _start) {
				startX = x;
				startY = y;
			}

			if (_chambers[y][x] == _end) {
				endX = x;
				endY = y;
			}
		}
			
		chamberArr->push(*subArr);
	}
	obj->add("chambers", *chamberArr);

	JSON::JSONObject *startObj = new JSON::JSONObject(obj);
	startObj->add("x", startX);
	startObj->add("y", startY);
	obj->add("start", *startObj);

	JSON::JSONObject *endObj = new JSON::JSONObject(obj);
	startObj->add("x", startX);
	startObj->add("y", startY);
	obj->add("start", *startObj);

	return *obj;
}

void Floor::deserialize(JSON::JSONObject &element) {

	JSON::JSONArray &chamberArr = element.getArray("chambers");
	for (int i = 0; i < chamberArr.size(); i++) {
		std::vector<Chamber*> vect;
		JSON::JSONArray &subArr = chamberArr.getArray(i);
		for (int j = 0; i < subArr.size(); i++) {
			JSON::JSONObject &chamberObj = subArr.getObject(i);
			Chamber *chamber = new Chamber();
			chamber->setFloor(*this);
			chamber->deserialize(chamberObj);
			vect.push_back(chamber);
		}
		_chambers.push_back(vect);
	}

	_start = _chambers[element.getObject("start").getInt("x")][element.getObject("start").getInt("y")];
	_end = _chambers[element.getObject("end").getInt("x")][element.getObject("end").getInt("y")];
}