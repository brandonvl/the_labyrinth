#pragma once
#include <JSONParser.h>
#include <string>
#include <vector>

class Monster;
class Item;
class Trap;

class FileManager
{
public:
	static void load();
	static void unload();
	static const std::string &getRandomSize(), &getRandomState(), &getRandomLightning(), &getRandomInventory(), &getRandomInventoryPosition();
	static Monster *getRandomMonster(const int minLevel, const int maxLevel), *getRandomBoss(const int minLevel, const int maxLevel);
	static Item *getRandomItem();
	static Trap *getRandomTrap();

private:
	static FileManager &instance();
	void init();

	struct ChamberOptions {
		std::vector<std::string> sizes, states, lightning, inventory, inventoryPositions;
	} _chamberOptions;

	std::vector<Monster*> _monsters, _bosses;
	std::vector<Item*> _items;
	std::vector<Trap*> _traps;
	JSON::JSONDocument *_document;

	FileManager() {}
};

