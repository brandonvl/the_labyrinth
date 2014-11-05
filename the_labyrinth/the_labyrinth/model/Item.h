#pragma once
#include "Thing.h"
#include "enums.h"

class Player;

class Item :
	public Thing
{
public:
	Item();
	virtual ~Item();

	const ItemType &getType() { return _type; }
	void setType(const ItemType &type) { _type = type; }
	const int getAmount() { return _amount; }
	void setAmount(const int amount) { _amount = amount; }
	void doEffect(Player &player);

private:
	ItemType _type;
	int _amount;
};

