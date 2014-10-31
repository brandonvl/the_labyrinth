#include "Dungeon.h"
#include "Floor.h"
#include "Chamber.h"
#include "model\enums.h"


Dungeon::Dungeon()
{
	_floors.reserve(4);
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
	for (unsigned int i = 0; i < _floors.capacity(); i++)
	{
		Floor *floor = new Floor();
		floor->createFloor(10, 1, 2);
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
}
