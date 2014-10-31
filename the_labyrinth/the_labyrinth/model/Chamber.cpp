#include "Chamber.h"
#include "Player.h"


Chamber::Chamber() : _explored(false), _player(nullptr), _visited(false)
{
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

const bool Chamber::hasNeighbour(const Direction &direction)
{
	return _neighbours.find(direction) != _neighbours.end();
}

void Chamber::enter(Player &player)
{
	if (player.getCurrentRoom() != nullptr) {
		player.getCurrentRoom()->setPlayer(nullptr);
	}

	player.setChamber(this);
	setPlayer(&player);

	if (!isVisited())
		_visited = true;
}
