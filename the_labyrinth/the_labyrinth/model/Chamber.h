#pragma once

#include <vector>;

class Player;
class Monster;

class Chamber
{
public:
	Chamber();
	virtual ~Chamber();
	Player *getPlayer() { return _player; }
	std::vector<Monster*> *getMonsters() { return &_monsters; }
private:
	Player *_player;
	std::vector<Monster*> _monsters;
};

