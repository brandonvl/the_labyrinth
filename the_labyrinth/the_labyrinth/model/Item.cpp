#include "Item.h"
#include "Player.h"

Item::Item()
{
}


Item::~Item()
{
}

void Item::doEffect(Player &player) {
	switch (_type) {
	case ItemType::ATTACK:
		player.addAttack(_amount);
		break;
	case ItemType::DEFENCE:
		player.addDefence(_amount);
		break;
	case ItemType::EXPERIENCE:
		player.addExperience(_amount);
		break;
	case ItemType::HEALTH:
		player.setHealth(_amount);
		break;
	case ItemType::LEVEL:
		player.setLevel(_amount);
		break;
	case ItemType::MAXHEALTH:
		player.setMaxHealth(_amount);
		break;
	case ItemType::PERCEPTION:
		player.setPerception(_amount);
		break;
	}
}

JSON::JSONElement *Item::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("type", static_cast<int>(_type));
	obj->add("amount", _amount);

	return obj;
}