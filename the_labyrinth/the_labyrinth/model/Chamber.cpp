#include "Chamber.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

Chamber::Chamber(const std::string size, const std::string state, const std::string lightning, const std::string furniture, const std::string furniturePosition) :
_explored(false), _player(nullptr), _visited(false), _size(size), _state(state), _lightning(lightning), _furniture(furniture), _furniturePosition(furniturePosition)
{
}

Chamber::~Chamber()
{
	for (auto it : _neighbours)
	{
		it.second = nullptr;
	}

	clearMonsters();
	
	_neighbours.clear();
}

void Chamber::clearMonsters()
{
	for (auto it : _monsters) {
		delete it;
	}

	_monsters.clear();
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

void Chamber::addItem(Item &item)
{
	_items.push_back(&item);
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
