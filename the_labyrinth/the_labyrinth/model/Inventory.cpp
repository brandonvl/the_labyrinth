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
