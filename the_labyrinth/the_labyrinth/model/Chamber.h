#pragma once

#include <vector>
#include <unordered_map>

class Player;
class Monster;

enum class Direction
{
	NORTH,WEST,EAST,SOUTH
};

class Chamber
{
public:
	Chamber();
	virtual ~Chamber();
	Player *getPlayer() { return _player; }
	std::vector<Monster*> *getMonsters() { return &_monsters; }
	const int getNeighbourCount() { return _neighbours.size(); }
	void addNeighbour(const Direction &direction, Chamber &chamber);
private:
	Player *_player;
	std::vector<Monster*> _monsters;
	std::unordered_map<Direction, Chamber*> _neighbours;
};

