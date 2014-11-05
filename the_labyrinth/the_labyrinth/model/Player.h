#pragma once
#include "Creature.h"
class Player :
	public Creature
{
public:
	Player();
	virtual ~Player();

	const int &getExperience() { return _experience; }
	void setExperience(const int &experience) { _experience = experience; }
	void addExperience(const int &experience) { _experience += experience; }
private:
	int _experience;
};

