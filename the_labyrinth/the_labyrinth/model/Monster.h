#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
public:
	Monster();
	virtual ~Monster();
	int getExperienceValue() { return _level * _baseExperience; }
	void setBaseExperience(const int &baseExperience) { _baseExperience = baseExperience; }
private:
	int _baseExperience;
};

