#include "Creature.h"
#include "Inventory.h"

Creature::Creature()
{
}

void Creature::setMaxHealth(const int &maxHealth, const bool &fillUpHealth)
{
	_maxHealthPoints = maxHealth;
	
	if (fillUpHealth)
		_healthPoints = maxHealth;
}

void Creature::addHealth(const int &health)
{
	_healthPoints += health;

	if (_healthPoints > _maxHealthPoints)
		_healthPoints = _maxHealthPoints;
	else if (_healthPoints < 0)
		_healthPoints = 0;
}


Creature::~Creature()
{
}

JSON::JSONElement *Creature::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(nullptr);

	obj->add("inventory", _inventory->serialize());

	// TODO: Serialize current room?

	obj->add("level", _level);
	obj->add("healthPoints", _healthPoints);
	obj->add("maxHealthPoints", _maxHealthPoints);
	obj->add("defense", _defense);
	obj->add("attack", _attack);
	obj->add("perception", _perception);
	obj->add("attackValue", _attackValue);

	return obj;
}