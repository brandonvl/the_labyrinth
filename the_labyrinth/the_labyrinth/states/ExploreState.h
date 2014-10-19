#pragma once
#include "GameState.h"
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
};

