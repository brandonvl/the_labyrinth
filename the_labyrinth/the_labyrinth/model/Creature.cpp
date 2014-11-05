#include "Creature.h"


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
