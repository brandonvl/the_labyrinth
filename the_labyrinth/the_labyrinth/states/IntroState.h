#pragma once
#include "GameState.h"

class IntroState :
	public GameState
{
public:
	virtual void init(Game &game) override;
	virtual void cleanUp() override;
	virtual void update() override;
	virtual void displayInfo() override;
	virtual void displayOptions() override;
	virtual void doOption() override;
	static IntroState &instance() {
		static IntroState _instance;

		return _instance;
	}
protected:
	IntroState() { }
private:
	void doOptionQuit();
	void doOptionPlay();
};

