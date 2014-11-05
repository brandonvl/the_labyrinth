#include "FileManager.h"
#include "RandomGenerator.h"

void FileManager::load() {
	if (instance()._document == nullptr) {
		instance()._document = JSON::JSONDocument::fromFile("data/settings");
		auto &root = instance()._document->getRootObject();
		auto &chamberOptions = root.getObject("chamber");

		auto &sizeOptions = chamberOptions.getArray("sizes");
		for (int i = 0; i < sizeOptions.size(); i++) {
			instance()._chamberOptions.sizes.push_back(sizeOptions.getString(i));
		}

		auto &stateOptions = chamberOptions.getArray("states");
		for (int i = 0; i < stateOptions.size(); i++) {
			instance()._chamberOptions.states.push_back(stateOptions.getString(i));
		}

		auto &lightningOptions = chamberOptions.getArray("lightning");
		for (int i = 0; i < lightningOptions.size(); i++) {
			instance()._chamberOptions.lightning.push_back(lightningOptions.getString(i));
		}

		auto &inventoryOptions = chamberOptions.getObject("inventory").getArray("items");
		for (int i = 0; i < inventoryOptions.size(); i++) {
			instance()._chamberOptions.inventory.push_back(inventoryOptions.getString(i));
		}

		auto &inventoryPositionOptions = chamberOptions.getObject("inventory").getArray("positions");
		for (int i = 0; i < inventoryPositionOptions.size(); i++) {
			instance()._chamberOptions.inventoryPositions.push_back(inventoryPositionOptions.getString(i));
		}
	}
}

void FileManager::unload() {
	delete instance()._document;
}

const std::string &FileManager::getRandomSize() {
	return RandomGenerator::randomFromVector(instance()._chamberOptions.sizes);
}

const std::string &FileManager::getRandomState() {
	return RandomGenerator::randomFromVector(instance()._chamberOptions.states);
}

const std::string &FileManager::getRandomLightning() {
	return RandomGenerator::randomFromVector(instance()._chamberOptions.lightning);
}

const std::string &FileManager::getRandomInventory() {
	return RandomGenerator::randomFromVector(instance()._chamberOptions.inventory);
}

const std::string &FileManager::getRandomInventoryPosition() {
	return RandomGenerator::randomFromVector(instance()._chamberOptions.inventoryPositions);
}

FileManager &FileManager::instance() {
	static FileManager _instance;
	return _instance;
}