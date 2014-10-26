#include "Floor.h"
#include "Chamber.h"

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
	Chamber *chamber = new Chamber();

	// make random chamber

	return *chamber;
}

void Floor::createMaze(const int &size)
{
	std::random_device dev;
	std::default_random_engine dre(dev());
	
	// DFS - Backtrack algo
	std::stack<ChamberEncap> _visitedCells;

	int totalCells = size * size;
	int visitedCells = 1;

	std::uniform_int_distribution<int> dist(0, size-1);
	int chosenX = dist(dre);
	int chosenY = dist(dre);

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
			std::uniform_int_distribution<int> suit(0, suitableChambers.size() - 1);
			ChamberEncap suitableChamber = suitableChambers[suit(dev)];
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
	chosenX = dist(dre);
	chosenY = dist(dre);

	_start = _chambers[chosenY][chosenX];

	chosenX = dist(dre);
	chosenY = dist(dre);
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
