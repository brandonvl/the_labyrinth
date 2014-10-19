#pragma once

class Player;
class GameState;
class Floor;

class Game
{
public:
	Game();
	virtual ~Game();
	Player &getPlayer() { return *_player; }
	void run();
	void stop();
	void changeState(GameState &state);
private:
	GameState *_state;
	Player *_player;
	Floor *_testFloor;
	bool _running;

};

