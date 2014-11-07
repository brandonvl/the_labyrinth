#pragma once
#include "JSONSerializable.h"

class Player;
class GameState;
class Dungeon;

class Game :
	public JSONSerializable
{
public:
	Game();
	virtual ~Game();
	Player &getPlayer() { return *_player; }
	Dungeon &getDungeon() { return *_dungeon; }
	void run();
	void stop();
	void changeState(GameState &state);
	void createDungeon(Player &player);
	JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	GameState *_state;
	Player *_player;
	Dungeon *_dungeon;
	bool _running;

};

