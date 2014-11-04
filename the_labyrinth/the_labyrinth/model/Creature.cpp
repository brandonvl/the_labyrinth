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


Creature::~Creature()
{
}
