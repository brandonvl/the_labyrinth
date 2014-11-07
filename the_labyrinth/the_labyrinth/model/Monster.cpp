#include "Monster.h"


Monster::Monster()
{
	_baseExperience = 0;
}


Monster::~Monster()
{
}

JSON::JSONElement &Monster::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("name", getName());
	obj->add("level", _level);
	obj->add("healthPoints", _healthPoints);
	obj->add("maxHealthPoints", _maxHealthPoints);
	obj->add("defense", _defense);
	obj->add("attack", _attack);
	obj->add("perception", _perception);
	obj->add("attackValue", _attackValue);
	obj->add("baseExperience", _baseExperience);

	return *obj;
}

void Monster::deserialize(JSON::JSONObject &element) {

	setName(element.getString("name"));
	_level = element.getInt("level");
	_healthPoints = element.getInt("healthPoints");
	_maxHealthPoints = element.getInt("maxHealthPoints");
	_defense = element.getInt("defense");
	_attack = element.getInt("attack");
	_perception = element.getInt("perception");
	_attackValue = element.getInt("attackValue");
	_baseExperience = element.getInt("baseExperience");
}