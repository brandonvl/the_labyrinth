#pragma once

#include <vector>
#include <unordered_map>
#include "enums.h"
#include "JSONSerializable.h"

class Player;
class Monster;
class Monster;
class Item;
class Trap;
class Floor;

class Chamber :
	public JSONSerializable
{
public:
	Chamber(const std::string size, const std::string state, const std::string lightning, const std::string furniture, const std::string furniturePosition);
	Chamber();
	virtual ~Chamber();
	Player *getPlayer() { return _player; }
	std::vector<Monster*> *getMonsters() { return &_monsters; }
	const int getNeighbourCount() { return _neighbours.size(); }
	void clearMonsters();
	const bool isExplored() { return _explored; }
	const bool isVisited() { return _visited; }
	void addNeighbour(const Direction &direction, Chamber &chamber);
	void addMonster(Monster &monster);
	void addItem(Item &item);
	void setTrap(Trap &trap) { _trap = &trap; }
	const bool hasNeighbour(const Direction &direction);
	std::unordered_map<Direction, Chamber*> *getNeighbours() { return &_neighbours; }
	Chamber *getNeighbour(const Direction &direction) { return hasNeighbour(direction) ?  _neighbours[direction] : nullptr; }
	Chamber *getRandomNeighbour();
	const Direction &getNeighBourDirection(Chamber &chamber);
	void enter(Player &player);
	void explore(Player &player);
	void setPlayer(Player *player) { _player = player; }
	const std::string &getSize() { return _size; }
	const std::string &getState() { return _state; }
	const std::string &getLightning() { return _lightning; }
	const std::string &getFurniture() { return _furniture; }
	const std::string &getFurniturePosition() { return _furniturePosition; }
	void setFloor(Floor &floor) { _floor = &floor; }
	Floor &getFloor() { return *_floor; }
	JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;
	
private:
	bool _explored;
	bool _visited;
	std::string _size, _state, _lightning, _furniture, _furniturePosition;

	Player *_player;
	std::vector<Monster*> _monsters;
	std::vector<Item*> _items;
	std::unordered_map<Direction, Chamber*> _neighbours;
	Trap *_trap;
	Floor *_floor;
};

