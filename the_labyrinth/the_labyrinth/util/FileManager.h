#pragma once
#include <JSONParser.h>
#include <string>
#include <vector>

class FileManager
{
public:
	static void load();
	static void unload();
	static const std::string &getRandomSize(), &getRandomState(), &getRandomLightning(), &getRandomInventory(), &getRandomInventoryPosition();

private:
	JSON::JSONDocument *_document;

	static FileManager &instance();

	struct ChamberOptions {
		std::vector<std::string> sizes, states, lightning, inventory, inventoryPositions;
	} _chamberOptions;

	FileManager() {}
};

