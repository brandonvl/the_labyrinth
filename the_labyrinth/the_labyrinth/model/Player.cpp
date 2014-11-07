#include "Player.h"
#include "Inventory.h"

const int EXPERIENCE_THRESHOLD = 50;

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

bool Player::isLevelUp()
{
	if (_level < 10){
		return _experience >= _level * EXPERIENCE_THRESHOLD;
	}
	else return false;
}

void Player::doLevelUp()
{
	if (_level < 10) {
		do
		{
			_level++;
			addAttack(1);
			addDefence(1);
			addMaxHealth(5, true);
			addAttackValue(2);
			addPerception(1);
		} while (_experience >= _level * EXPERIENCE_THRESHOLD && _level < 10);
	}
}


Player::~Player()
{
	delete _inventory;
}

JSON::JSONElement &Player::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("name", getName());
	obj->add("level", _level);
	obj->add("healthPoints", _healthPoints);
	obj->add("maxHealthPoints", _maxHealthPoints);
	obj->add("defense", _defense);
	obj->add("attack", _attack);
	obj->add("perception", _perception);
	obj->add("attackValue", _attackValue);
	obj->add("experience", _experience);
	obj->add("inventory", _inventory->serialize());


	return *obj;
}

void Player::deserialize(JSON::JSONObject &element) {
	setName(element.getString("name"));
	_level = element.getInt("level");
	_healthPoints = element.getInt("healthPoints");
	_maxHealthPoints = element.getInt("maxHealthPoints");
	_defense = element.getInt("defense");
	_attack = element.getInt("attack");
	_perception = element.getInt("perception");
	_attackValue = element.getInt("attackValue");
	_experience = element.getInt("experience");
	_inventory->deserialize(element.getObject("inventory"));
}