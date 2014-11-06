#include "Chamber.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Trap.h"

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