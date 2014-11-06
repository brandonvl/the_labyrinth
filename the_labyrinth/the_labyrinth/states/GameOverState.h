#pragma once
#include "GameState.h"

class Player;

class GameOverState :
	public GameState
{
public:
	virtual void init(Game &game) override;
	virtual void cleanUp() override;
	virtual void update() override;
	virtual void displayInfo() override;
	virtual void displayOptions() override;
	virtual void doOption() override;
	static GameOverState &instance() {
		static GameOverState _instance;
		return _instance;
	}
protected:
	GameOverState() { }
private:
	Player *_player;
};

