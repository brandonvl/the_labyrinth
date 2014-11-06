#include "Monster.h"


Monster::Monster()
{
	_baseExperience = 0;
}


Monster::~Monster()
{
}

JSON::JSONElement *Monster::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("level", _level);
	obj->add("healthPoints", _healthPoints);
	obj->add("maxHealthPoints", _maxHealthPoints);
	obj->add("defense", _defense);
	obj->add("attack", _attack);
	obj->add("perception", _perception);
	obj->add("attackValue", _attackValue);
	obj->add("baseExperience", _baseExperience);

	return obj;
}