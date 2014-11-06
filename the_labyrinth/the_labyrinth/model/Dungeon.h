#pragma once
#include "JSONSerializable.h"
#include <vector>

class Floor;
class Chamber;

class Dungeon :
	public JSONSerializable
{
public:
	Dungeon();
	virtual ~Dungeon();
	void createDungeon();
	Floor *getCurrentFloor() { return _currentFloor; }
	Chamber &getDungeonStart() { return *_start; }
	Chamber &getDungeonEnd() { return *_end; }
	JSON::JSONElement *serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	Floor &createFloor();
	std::vector<Floor*> _floors;
	Floor *_currentFloor;
	Chamber *_start;
	Chamber *_end;

};

