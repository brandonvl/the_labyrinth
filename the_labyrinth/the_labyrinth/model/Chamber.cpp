#include "Chamber.h"


Chamber::Chamber()
{
	_player = nullptr;
	_monsters = std::vector<Monster*>();
	_neighbours = std::unordered_map<Direction,Chamber*>();
}


Chamber::~Chamber()
{
	for (auto it : _neighbours)
	{
		it.second = nullptr;
	}

	_monsters.clear();
	_neighbours.clear();
}

void Chamber::addNeighbour(const Direction &direction, Chamber &chamber)
{
	_neighbours.insert(std::make_pair(direction, &chamber));
}
