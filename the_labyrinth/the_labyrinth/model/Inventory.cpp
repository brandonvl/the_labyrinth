#include "Inventory.h"
#include "Item.h"
#include "Player.h"

Inventory::Inventory(Player &owner) : _owner(&owner)
{
}


Inventory::~Inventory()
{
}

void Inventory::addItem(Item &item) {
	if (_items.count(&item)) {
		_items[&item]++;
	}
	else {
		_items.insert(std::make_pair(&item, 1));
	}
}

void Inventory::useItem(Item &item) {
	auto it = _items.find(&item);
	if (it != _items.end()) {
		item.doEffect(*_owner);
		_items.erase(_items.find(&item));
	}
}

JSON::JSONElement &Inventory::serialize(JSON::JSONElement *parent) {
	JSON::JSONObject *obj = new JSON::JSONObject(parent);


	JSON::JSONArray *itemArr = new JSON::JSONArray(obj);
	for (auto item : _items) {
		for (int i = 0; i < item.second; i++)
			itemArr->push(item.first->serialize());
	}
	obj->add("items", *itemArr);

	return *obj;
}

void Inventory::deserialize(JSON::JSONObject &element) {

	JSON::JSONArray &itemArr = element.getArray("items");
	for (int i = 0; i < itemArr.size(); i++) {
		Item *item = new Item();
		item->deserialize(itemArr.getObject(i));
		addItem(*item);
	}


}