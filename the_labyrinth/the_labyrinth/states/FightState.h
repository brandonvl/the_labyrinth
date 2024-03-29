#pragma once
#include "GameState.h"
#include <vector>

class Creature;
class Player;
class Monster;

class FightState :
	public GameState
{
public:
	virtual void init(Game &game) override;
	virtual void cleanUp() override;
	virtual void update() override;
	virtual void displayInfo() override;
	virtual void displayOptions() override;
	virtual void doOption() override;
	static FightState &instance() {
		static FightState _instance;

		return _instance;
	}
	void setUserInitiated() { _userInitiated = true; }
protected:
	FightState() { }
private:
	bool _userInitiated = false;
	bool _hasFled = false;
	Player *_player;
	std::vector<Monster*> *_monsters;
	void doDisplayMonsterInfo();
	void doDisplayPlayerStatus();
	void doMonsterActions();
	void doOptionFlee();
	void doOptionFight();
	void doOptionInventory();
	void doCheckMonsterHealth();
	int doCombat(Creature &attacker, Creature &defender);
};