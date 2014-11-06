#include "SaveGameManager.h"
#include <JSONParser.h>
#include "model\Game.h"

SaveGameManager::SaveGameManager()
{
}


SaveGameManager::~SaveGameManager()
{
}

void SaveGameManager::saveGame(Game &game) {
	JSON::JSONDocument *doc = JSON::JSONDocument::fromRoot(*game.serialize());
	doc->saveFile("data/savegame");
	delete doc;
}

Game *SaveGameManager::loadGame() {
	return nullptr;
}