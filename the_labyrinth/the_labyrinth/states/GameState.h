#pragma once

#include <iostream>
#include <string>

class Game;

class GameState
{
public:
	//virtual ~GameState();
	virtual void init(Game &game) = 0;
	virtual void cleanUp() = 0;
	virtual void update() = 0;
	virtual void displayInfo();
	virtual void displayOptions();
	virtual void doOption();
	void changeState(GameState &state);
protected:
	GameState() {}
	Game *_game;
	std::string _chosenOption;
	void doOptionQuit();
};

