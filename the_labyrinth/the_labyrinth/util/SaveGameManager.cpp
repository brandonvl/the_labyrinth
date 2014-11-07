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
		for (int i = 0; i < it.second->size(); i++) {
			JSON::JSONObject &neighbourObj = it.second->getObject(i);
			Direction direction = static_cast<Direction>(neighbourObj.getInt("direction"));
			Chamber *chamber = nullptr;
			int x = neighbourObj.getInt("x");
			int y = neighbourObj.getInt("y");

			if (x > 0 && y > 0) {
				if (direction == Direction::UPSTAIRS) {
					Floor *floor = it.first->getFloor().getDungeon()->getNextFloor(it.first->getFloor());
					if (floor != nullptr) chamber = floor->getChamber(y, x);
				}
				else if (direction == Direction::DOWNSTAIRS){
					Floor *floor = it.first->getFloor().getDungeon()->getPreviousFloor(it.first->getFloor());
					if (floor != nullptr) chamber = floor->getChamber(y, x);
				}
				else {
					chamber = it.first->getFloor().getChamber(y, x);
				}
			}
			
			it.first->addNeighbour(direction, *chamber);
		}
	}
}