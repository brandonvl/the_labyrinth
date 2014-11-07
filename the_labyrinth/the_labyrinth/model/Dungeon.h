#pragma once
#include "JSONSerializable.h"
#include <vector>

class Floor;
class Chamber;
class Game;

class Dungeon :
	public JSONSerializable
{
public:
	Dungeon();
	virtual ~Dungeon();
	void createDungeon();
	Floor *getCurrentFloor() { return _currentFloor; }
	void setNextFloor();
	void setPreviousFloor();
	Floor *getNextFloor(Floor &floor);
	Floor *getPreviousFloor(Floor &floor);
	int getFloorIndex(Floor &floor);
	Chamber &getDungeonStart() { return *_start; }
	Chamber &getDungeonEnd() { return *_end; }
	void setGame(Game &game) { _game = &game; }
	Game *getGame() { return _game; }
	JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	Floor &createFloor();
	std::vector<Floor*> _floors;
	Floor *_currentFloor;
	Chamber *_start;
	Chamber *_end;
	Game *_game;

};

