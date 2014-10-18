#pragma once

class Player;
class GameState;

class Game
{
public:
	Game();
	virtual ~Game();
	Player &getPlayer();
	void run();
	void stop();
	void changeState(GameState &state);
private:
	GameState *_state;
	Player *_player;
	bool _running;

};

