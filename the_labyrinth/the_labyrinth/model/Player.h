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
	bool hasWon() { return (_healthPoints > 0); } // determine if the player has won the game
	JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	int _experience;
};

