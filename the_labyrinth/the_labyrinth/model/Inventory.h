#pragma once
#include "JSONSerializable.h"
#include <unordered_map>

class Item;
class Player;

class Inventory :
	public JSONSerializable
{
public:
	Inventory(Player &owner);
	virtual ~Inventory();
	int getItemCount() { return _items.size(); }
	void addItem(Item &item);
	void useItem(Item &item);
	void setOwner(Player &owner) { _owner = &owner; }
	const std::unordered_map<Item*, int> &getItems() { return _items; }
	JSON::JSONElement *serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	std::unordered_map<Item*,int> _items;
	Player *_owner;
};

