#pragma once
#include "Creature.h"
class Player :
	public Creature
{
public:
	Player();
	virtual ~Player();
private:
	int _experience;
};

