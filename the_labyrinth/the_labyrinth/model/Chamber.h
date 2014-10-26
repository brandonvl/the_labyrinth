#pragma once

#include <vector>
#include <unordered_map>

class Player;
class Monster;

enum class Direction
{
	NORTH = 1, SOUTH = 2, WEST = 3, EAST = 4, UPSTAIRS = 5, DOWNSTAIRS = 6
};

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
private:
	bool _explored;
	bool _visited;
	Player *_player;
	std::vector<Monster*> _monsters;
	std::unordered_map<Direction, Chamber*> _neighbours;
};

