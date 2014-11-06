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

	obj->add("level", _level);
	obj->add("healthPoints", _healthPoints);
	obj->add("maxHealthPoints", _maxHealthPoints);
	obj->add("defense", _defense);
	obj->add("attack", _attack);
	obj->add("perception", _perception);
	obj->add("attackValue", _attackValue);
	obj->add("experience", _experience);

	return obj;
}

void Player::deserialize(JSON::JSONObject &element) {
	_level = element.getInt("level");
	_healthPoints = element.getInt("healthPoints");
	_maxHealthPoints = element.getInt("maxHealthPoints");
	_defense = element.getInt("defense");
	_attack = element.getInt("attack");
	_perception = element.getInt("perception");
	_experience = element.getInt("experience");
}