#include "Trap.h"
#include "Player.h"

Trap::Trap()
{
}


Trap::~Trap()
{
}

void Trap::doEffect(Player &player) {
	player.addHealth(-_damage);
}