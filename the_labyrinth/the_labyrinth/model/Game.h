#pragma once

class Player;
class GameState;
class Dungeon;

class Game
{
public:
	Game();
	virtual ~Game();
	Player &getPlayer() { return *_player; }
	Dungeon &getDungeon() { return *_dungeon; }
	void run();
	void stop();
	void changeState(GameState &state);
	void createDungeon();
private:
	GameState *_state;
	Player *_player;
	Dungeon *_dungeon;
	bool _running;

};

