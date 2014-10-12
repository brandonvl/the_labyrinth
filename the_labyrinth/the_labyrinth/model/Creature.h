#pragma once

#include "Thing.h"

class Inventory;

class Creature : public Thing
{
public:
	Creature();
	virtual ~Creature();
	int getLevel() { return _level; }
	int getHealth() { return _healthPoints; }
	int getMaxHealth() { return _maxHealthPoints; }
	int getDefense() { return _defense; }
	int getAttack() { return _attack; }
	int getPerception() { return _perception; }
	Inventory *getInventory() { return _inventory; }
protected:
	Inventory *_inventory;
	int _level;
	int _experience;
	int _healthPoints;
	int _maxHealthPoints;
	int _defense;
	int _attack;
	int _perception;

};

