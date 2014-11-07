#include "Chamber.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Trap.h"
#include "util\RandomGenerator.h"
#include <algorithm>
#include "Inventory.h"

Chamber::Chamber(const std::string size, const std::string state, const std::string lightning, const std::string furniture, const std::string furniturePosition) :
_explored(false), _player(nullptr), _visited(false), _size(size), _state(state), _lightning(lightning), _furniture(furniture), _furniturePosition(furniturePosition)
{
}

Chamber::Chamber(){}

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

	
	_items.clear();
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
	if (_trap != nullptr) {
		int exploreroll = RandomGenerator::random(player.getPerception() / 2, 10);

		if (exploreroll > 6)
			_trap->dismantle();
	}

	// explore code (determine threshold)

	for (auto it : _items)
	{
		player.getInventory()->addItem(*it);
	}

	_items.clear();
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

JSON::JSONElement *Chamber::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);
	obj->add("hasPlayer", (_player != nullptr));

	// add monsters 
	JSON::JSONArray *monsterArr = new JSON::JSONArray(obj);
	for (auto monster : _monsters)
		monsterArr->push(monster->serialize());
	obj->add("monsters", monsterArr);

	// add items 
	JSON::JSONArray *itemArr = new JSON::JSONArray(obj);
	for (auto item : _items)
		monsterArr->push(item->serialize());
	obj->add("items", itemArr);

	// TODO: Serialize neighbours

	obj->add("trap", _trap->serialize());

	return obj;
}

void Chamber::deserialize(JSON::JSONObject &element) {

	// TODO: Set player pointer

	JSON::JSONArray &monsterArr = element.getArray("monsters");
	for (int i = 0; i > monsterArr.size(); i++) {
		Monster *monster = new Monster();
		monster->deserialize(monsterArr.getObject(i));
		_monsters.push_back(monster);
	}

	JSON::JSONArray &itemArr = element.getArray("items");
	for (int i = 0; i > itemArr.size(); i++) {
		Item *item = new Item();
		item->deserialize(itemArr.getObject(i));
		_items.push_back(item);
	}

	// TODO: Deserialize neighbours

	_trap = new Trap();
	_trap->deserialize(element.getObject("trap"));
}