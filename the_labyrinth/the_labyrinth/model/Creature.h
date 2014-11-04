#pragma once

#include "Thing.h"

class Inventory;
class Chamber;

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
	Inventory &getInventory() { return *_inventory; }
	Chamber *getCurrentRoom() { return _currentRoom; }
	void setChamber(Chamber *chamber) { _currentRoom = chamber; }
	void setLevel(const int &level) { _level = level; }
	void setHealth(const int &health) { _healthPoints = health; }
	void setMaxHealth(const int &maxHealth, const bool &fillUpHealth = false);
	void setDefense(const int &defense) { _defense = defense; }
	void setAttack(const int &attack) { _attack = attack; }
	void setPerception(const int &perception) { _perception = perception; }
protected:
	Inventory *_inventory;
	Chamber *_currentRoom;
	int _level;
	int _healthPoints;
	int _maxHealthPoints;
	int _defense;
	int _attack;
	int _perception;

};

