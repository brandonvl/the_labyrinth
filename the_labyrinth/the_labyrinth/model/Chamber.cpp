#include "Chamber.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Trap.h"
#include "util\RandomGenerator.h"
#include <algorithm>

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

	for (auto it : _items)
		delete it;

	delete _trap;

	
	
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

void Chamber::explore(Player &player)
{
	int exploreroll = RandomGenerator::random(0, player.getPerception());

	// explore code (determine threshold)

	_explored = true;
}

Chamber *Chamber::getRandomNeighbour()
{
	if (_neighbours.size() > 0)
	{
		int randomRoll = RandomGenerator::random(0, _neighbours.size() - 1);
		auto iterator = _neighbours.begin();
		std::advance(iterator, randomRoll);

		return iterator->second;
	}
	else
		return nullptr;
}

const Direction &Chamber::getNeighBourDirection(Chamber &chamber)
{
	auto lamba = [&chamber](std::pair<Direction, Chamber*> value){ return value.second == &chamber; };
	auto keyValue = std::find_if(_neighbours.begin(), _neighbours.end(), lamba);

	if (keyValue != _neighbours.end())
		return (*keyValue).first;
	else
		return Direction::INVALID;
}
