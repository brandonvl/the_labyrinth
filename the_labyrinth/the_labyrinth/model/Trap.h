#pragma once
#include "Thing.h"

class Player;

class Trap :
	public Thing
{
public:
	Trap();
	virtual ~Trap();

	const int getDamage() { return _damage; }
	void setDamage(int damage) { _damage = damage; }
	void doEffect(Player &player);
	bool isDismantled() { return _dismantled; }
	void dismantle() { _dismantled = true; }
	JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override;
	void deserialize(JSON::JSONObject &element) override;

private:
	int _damage;
	bool _dismantled;
};

