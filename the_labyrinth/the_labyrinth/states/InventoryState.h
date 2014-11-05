#pragma once
#include "GameState.h"

class Player;

class InventoryState :
	public GameState
{
public:
	virtual void init(Game &game) override;
	virtual void cleanUp() override;
	virtual void update() override;
	virtual void displayInfo() override;
	virtual void displayOptions() override;
	virtual void doOption() override;
	static InventoryState &instance() {
		static InventoryState _instance;
		return _instance;
	}
protected:
	InventoryState() { }
private:
	Player *_player;
};

