#pragma once

#include <vector>

class Floor;

class Dungeon
{
public:
	Dungeon();
	virtual ~Dungeon();
private:
	Floor &createFloor();
	std::vector<Floor*> _floors;
};

