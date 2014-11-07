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
		player.addHealth(_amount);
		break;
	case ItemType::MAXHEALTH:
		player.addMaxHealth(_amount, true);
		break;
	case ItemType::PERCEPTION:
		player.addPerception(_amount);
		break;
	case ItemType::ATTACKVALUE:
		player.addAttackValue(_amount);
		break;
	}
}

JSON::JSONElement &Item::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);

	obj->add("name", getName());
	obj->add("type", static_cast<int>(_type));
	obj->add("amount", _amount);

	return *obj;
}

void Item::deserialize(JSON::JSONObject &element) {
	setName(element.getString("name"));
	_type = static_cast<ItemType>(element.getInt("type"));
	_amount = element.getInt("amount");
}