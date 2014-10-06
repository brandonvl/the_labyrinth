#pragma once

#include <string>

class Inventory;

class Creature
{
public:
	Creature();
	virtual ~Creature();
protected:
	Inventory *_inventory;
	std::string _name;
	int _level;
	int _experience;
	int _healthPoints;
	int _maxHealthPoints;
	int _defense;
	int _attack;
	int _perception;

};

