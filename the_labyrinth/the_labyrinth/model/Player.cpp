#include "Player.h"
#include "Inventory.h"

Player::Player()
{
	setMaxHealth(15, true);
	setLevel(1);
	_experience = 0;
	setAttackValue(5);
	setDefense(5);
	setAttack(5);
	setPerception(5);
	_inventory = new Inventory(*this);
}


Player::~Player()
{
	delete _inventory;
}

JSON::JSONElement *Player::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	return obj;
}