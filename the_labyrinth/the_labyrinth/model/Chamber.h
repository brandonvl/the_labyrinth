#pragma once

#include <vector>
#include <unordered_map>
#include "enums.h"

class Player;
class Monster;
class Inventory;
class Monster;
class Item;
class Trap;

class Chamber
{
public:
	Chamber(const std::string size, const std::string state, const std::string lightning, const std::string inventory, const std::string inventoryPosition);
	virtual ~Chamber();
	Player *getPlayer() { return _player; }
	std::vector<Monster*> *getMonsters() { return &_monsters; }
	const int getNeighbourCount() { return _neighbours.size(); }
	const bool isExplored() { return _explored; }
	const bool isVisited() { return _visited; }
	void addNeighbour(const Direction &direction, Chamber &chamber);
	void addMonster(Monster &monster);
	void addItem(Item &item);
	void setTrap(Trap &trap) { _trap = &trap; }
	const bool hasNeighbour(const Direction &direction);
	std::unordered_map<Direction, Chamber*> *getNeighbours() { return &_neighbours; }
	Chamber *getNeighbour(const Direction &direction) { return hasNeighbour(direction) ?  _neighbours[direction] : nullptr; }
	void enter(Player &player);
	void setPlayer(Player *player) { _player = player; }
	const std::string &getSize() { return _size; }
	const std::string &getState() { return _state; }
	const std::string &getLightning() { return _lightning; }
	const std::string &getInventory() { return _inventory; }
	const std::string &getInventoryPosition() { return _inventoryPosition; }
	
private:
	bool _explored;
	bool _visited;
	const std::string _size, _state, _lightning, _inventory, _inventoryPosition;

	Player *_player;
	std::vector<Monster*> _monsters;
	std::vector<Item*> _items;
	std::vector<Inventory*> _inventories;
	std::unordered_map<Direction, Chamber*> _neighbours;
	Trap *_trap;
};

