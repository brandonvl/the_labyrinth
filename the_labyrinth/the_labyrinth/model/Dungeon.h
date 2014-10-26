#pragma once

#include <vector>

class Floor;
class Chamber;

class Dungeon
{
public:
	Dungeon();
	virtual ~Dungeon();
	void createDungeon();
	Floor *getCurrentFloor() { return _currentFloor; }
	Chamber &getDungeonStart() { return *_start; }
	Chamber &getDungeonEnd() { return *_end; }
private:
	Floor &createFloor();
	std::vector<Floor*> _floors;
	Floor *_currentFloor;
	Chamber *_start;
	Chamber *_end;

};

