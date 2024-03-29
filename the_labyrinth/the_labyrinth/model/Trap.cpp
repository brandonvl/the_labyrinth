#include "Trap.h"
#include "Player.h"

Trap::Trap() : _dismantled(false)
{
}


Trap::~Trap()
{
}

void Trap::doEffect(Player &player) {
	player.addHealth(-_damage);
}

JSON::JSONElement &Trap::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("damage", _damage);
	obj->add("dismantled", _dismantled);

	return *obj;
}

void Trap::deserialize(JSON::JSONObject &element) {
	_damage = element.getInt("damage");
	_dismantled = element.getInt("dismantled");
}