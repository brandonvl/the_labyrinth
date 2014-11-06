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
	JSON::JSONElement *serialize(JSON::JSONElement *parent = nullptr) override;

private:
	int _damage;
};

