#include "FileManager.h"
#include "RandomGenerator.h"
#include "model\Monster.h"

void FileManager::load() {
	instance().init();
}

void FileManager::init() {
	if (_document == nullptr) {
		_document = JSON::JSONDocument::fromFile("data/settings");
		auto &root = _document->getRootObject();
		auto &chamberOptions = root.getObject("chamber");

		auto &sizeOptions = chamberOptions.getArray("sizes");
		for (int i = 0; i < sizeOptions.size(); i++) {
			_chamberOptions.sizes.push_back(sizeOptions.getString(i));
		}

		auto &stateOptions = chamberOptions.getArray("states");
		for (int i = 0; i < stateOptions.size(); i++) {
			_chamberOptions.states.push_back(stateOptions.getString(i));
		}

		auto &lightningOptions = chamberOptions.getArray("lightning");
		for (int i = 0; i < lightningOptions.size(); i++) {
			_chamberOptions.lightning.push_back(lightningOptions.getString(i));
		}

		auto &inventoryOptions = chamberOptions.getObject("inventory").getArray("items");
		for (int i = 0; i < inventoryOptions.size(); i++) {
			_chamberOptions.inventory.push_back(inventoryOptions.getString(i));
		}

		auto &inventoryPositionOptions = chamberOptions.getObject("inventory").getArray("positions");
		for (int i = 0; i < inventoryPositionOptions.size(); i++) {
			_chamberOptions.inventoryPositions.push_back(inventoryPositionOptions.getString(i));
		}

		auto &monsterOptions = root.getArray("monsters");
		for (int i = 0; i < monsterOptions.size(); i++) {
			JSON::JSONObject &obj = monsterOptions.getObject(i);
			Monster *monster = new Monster();
			monster->setName(obj.getString("name"));
			monster->setLevel(obj.getInt("level"));
			monster->setMaxHealth(obj.getInt("health"), true);
			monster->setAttack(obj.getInt("attack"));
			monster->setDefense(obj.getInt("defense"));
			monster->setPerception(obj.getInt("perception"));
			monster->setBaseExperience(obj.getInt("baseExperience"));
			_monsters.push_back(monster);
		}

		auto &bossOptions = root.getArray("bosses");
		for (int i = 0; i < monsterOptions.size(); i++) {
			JSON::JSONObject &obj = monsterOptions.getObject(i);
			Monster *monster = new Monster();
			monster->setName(obj.getString("name"));
			monster->setLevel(11);
			monster->setMaxHealth(obj.getInt("health"), true);
			monster->setAttack(obj.getInt("attack"));
			monster->setDefense(obj.getInt("defense"));
			monster->setPerception(obj.getInt("perception"));
			monster->setBaseExperience(obj.getInt("baseExperience"));
			_bosses.push_back(monster);
		}
	}
}

void FileManager::unload() {
	for (auto monster : instance()._monsters)
		delete monster;

	instance()._monsters.clear();
	delete instance()._document;
}

const std::string &FileManager::getRandomSize() {
	return RandomGenerator::randomFromVector<std::string>(instance()._chamberOptions.sizes);
}

const std::string &FileManager::getRandomState() {
	return RandomGenerator::randomFromVector<std::string>(instance()._chamberOptions.states);
}

const std::string &FileManager::getRandomLightning() {
	return RandomGenerator::randomFromVector<std::string>(instance()._chamberOptions.lightning);
}

const std::string &FileManager::getRandomInventory() {
	return RandomGenerator::randomFromVector<std::string>(instance()._chamberOptions.inventory);
}

const std::string &FileManager::getRandomInventoryPosition() {
	return RandomGenerator::randomFromVector<std::string>(instance()._chamberOptions.inventoryPositions);
}

Monster *FileManager::getRandomMonster(const int minLevel, const int maxLevel) {
	std::vector<Monster*> monsters;
	for (auto monster : instance()._monsters) {
		if (monster->getLevel() >= minLevel && monster->getLevel() <= maxLevel)
			monsters.push_back(monster);
	}
	Monster *monster = RandomGenerator::randomFromVector<Monster*>(monsters);
	if (monster != nullptr) return new Monster(*monster);
	return nullptr;
}

Monster *FileManager::getRandomBoss(const int minLevel, const int maxLevel) {
	Monster *monster = RandomGenerator::randomFromVector<Monster*>(instance()._bosses);
	if (monster != nullptr) return new Monster(*monster);
	return nullptr;
}

FileManager &FileManager::instance() {
	static FileManager _instance;
	return _instance;
}