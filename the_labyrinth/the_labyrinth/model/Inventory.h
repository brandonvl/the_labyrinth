#pragma once

#include <unordered_map>

class Item;

class Inventory
{
public:
	Inventory();
	virtual ~Inventory();
	int getItemCount(const Item &item);
private:
	std::unordered_map<Item*,int> _items;
};

