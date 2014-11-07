#pragma once
#include "GameState.h"

class Player;
class Item;

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
	void setFightStateSend() { _fightStateSend = true; }
	static InventoryState &instance() {
		static InventoryState _instance;
		return _instance;
	}
protected:
	InventoryState() { }
private:
	void doOptionBack();
	void doOptionUse();
	std::string getItemTypeText(Item &item);
	Player *_player;
	bool _fightStateSend = false;
};

