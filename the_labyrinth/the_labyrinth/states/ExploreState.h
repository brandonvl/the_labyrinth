#pragma once
#include "GameState.h"

class Chamber;
class Player;

class ExploreState :
	public GameState
{
public:
	virtual void init(Game &game) override;
	virtual void cleanUp() override;
	virtual void update() override;
	virtual void displayInfo() override;
	virtual void displayOptions() override;
	virtual void doOption() override;
	static ExploreState &instance() {
		static ExploreState _instance;

		return _instance;
	}
protected:
	ExploreState() { }
	//virtual ~ExploreState();
private:
	void showMap();
	void showMapInfo();
	void showChamber(Chamber *cham);
	void doOptionQuit();
	void doOptionMove(Player &player, Chamber &chamber);
	void doOptionShowMap();
	void doOptionExplore();
	void doOptionShowStatus(Player &player);
	void doOptionFight();

	const bool TEST_MODE = false;
};

