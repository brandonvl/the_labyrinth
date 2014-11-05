#include "Chamber.h"
#include "Player.h"
#include "Monster.h"


Chamber::Chamber(const std::string size, const std::string state, const std::string lightning, const std::string inventory, const std::string inventoryPosition) :
_explored(false), _player(nullptr), _visited(false), _size(size), _state(state), _lightning(lightning), _inventory(inventory), _inventoryPosition(inventoryPosition)
{
}


Chamber::~Chamber()
{
	for (auto it : _neighbours)
	{
		it.second = nullptr;
	}

	for (auto it : _monsters) 
	{
		delete it;
	}

	_monsters.clear();
	_neighbours.clear();
}

void Chamber::addNeighbour(const Direction &direction, Chamber &chamber)
{
	_neighbours.insert(std::make_pair(direction, &chamber));
}

void Chamber::addMonster(Monster &monster)
{
	monster.setChamber(this);
	_monsters.push_back(&monster);
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
