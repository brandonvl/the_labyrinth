#include "Player.h"


Player::Player()
{
	setMaxHealth(15, true);
	setLevel(1);
	_experience = 0;
	setDefense(5);
	setAttack(5);
	setPerception(5);
}


Player::~Player()
{
}
