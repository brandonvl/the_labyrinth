#include "SaveGameManager.h"
#include <JSONParser.h>
#include "model\Game.h"
#include "model\enums.h"
#include "model\Chamber.h"
#include "model\Floor.h"
#include "model\Dungeon.h"

void SaveGameManager::saveGame(Game &game) {
	JSON::JSONDocument *doc = JSON::JSONDocument::fromRoot(game.serialize());
	doc->saveFile("data/savegame");
	delete doc;
}

void SaveGameManager::loadGame(Game *game) {
	JSON::JSONDocument *doc = JSON::JSONDocument::fromFile("data/savegame");
	game->deserialize(doc->getRootObject());
	instance().attachNeightbours();
	delete doc;
}

void SaveGameManager::attachNeightbours() {
	for (auto it : _attachNeightbourList) {
		for (int i = 0; i > it.second->size(); i++) {
			JSON::JSONObject &neighbourObj = it.second->getObject(i);
			Direction direction = static_cast<Direction>(neighbourObj.getInt("direction"));
			Chamber *chamber = nullptr;

			switch (direction) {
			case Direction::UPSTAIRS:
				chamber = (&it.first->getFloor() + 1)->getChamber(neighbourObj.getInt("y"), neighbourObj.getInt("x"));
				break;
			case Direction::DOWNSTAIRS:
				chamber = (&it.first->getFloor() - 1)->getChamber(neighbourObj.getInt("y"), neighbourObj.getInt("x"));
				break;
			default:
				chamber = it.first->getFloor().getChamber(neighbourObj.getInt("y"), neighbourObj.getInt("x"));
				break;
			}
			
			if (chamber != nullptr)
				it.first->addNeighbour(direction, *chamber);
		}
	}
}