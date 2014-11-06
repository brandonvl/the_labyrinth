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

JSON::JSONElement *Trap::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("damage", _damage);
	obj->add("dismantled", _dismantled);

	return obj;
}