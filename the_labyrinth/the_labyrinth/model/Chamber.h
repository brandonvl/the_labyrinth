#pragma once

#include <vector>
#include <unordered_map>
#include "enums.h"

class Player;
class Monster;
class Inventory;

class Chamber
{
public:
	Chamber(const ChamberSize size, const ChamberState state, const ChamberLightning lightning, const ChamberInventory inventory, const ChamberInventoryPosition inventoryPosition);
	virtual ~Chamber();
	Player *getPlayer() { return _player; }
	std::vector<Monster*> *getMonsters() { return &_monsters; }
	const int getNeighbourCount() { return _neighbours.size(); }
	const bool isExplored() { return _explored; }
	const bool isVisited() { return _visited; }
	void addNeighbour(const Direction &direction, Chamber &chamber);
	const bool hasNeighbour(const Direction &direction);
	std::unordered_map<Direction, Chamber*> *getNeighbours() { return &_neighbours; }
	Chamber *getNeighbour(const Direction &direction) { return hasNeighbour(direction) ?  _neighbours[direction] : nullptr; }
	void enter(Player &player);
	void setPlayer(Player *player) { _player = player; }
	const ChamberSize &getSize() { return _size; }
	const ChamberState &getState() { return _state; }
	const ChamberLightning &getLightning() { return _lightning; }
	const ChamberInventory &getInventory() { return _inventory; }
	const ChamberInventoryPosition &getInventoryPosition() { return _inventoryPosition; }
	
private:
	bool _explored;
	bool _visited;
	const ChamberSize _size;
	const ChamberState _state;
	const ChamberLightning _lightning;
	const ChamberInventory _inventory;
	const ChamberInventoryPosition _inventoryPosition;

	Player *_player;
	std::vector<Monster*> _monsters;
	std::vector<Inventory*> _inventories;
	std::unordered_map<Direction, Chamber*> _neighbours;
};

