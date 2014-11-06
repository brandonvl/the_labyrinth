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

	return obj;
}