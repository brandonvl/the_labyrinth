#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
public:
	Monster();
	virtual ~Monster();
	int getExperienceValue() { return _baseExperience; }
	void setBaseExperience(const int &baseExperience) { _baseExperience = baseExperience; }
	JSON::JSONElement *serialize(JSON::JSONElement *parent = nullptr) override;

private:
	int _baseExperience;
};

