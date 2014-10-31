#pragma once

#include <vector>
#include <unordered_map>
#include "enums.h"

class Player;
class Monster;

class Chamber
{
public:
	Chamber();
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
private:
	bool _explored;
	bool _visited;
	Player *_player;
	std::vector<Monster*> _monsters;
	std::unordered_map<Direction, Chamber*> _neighbours;
};

