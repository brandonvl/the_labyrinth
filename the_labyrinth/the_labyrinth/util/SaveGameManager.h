#pragma once
#include <map>

class Game;
class Chamber;

namespace JSON { class JSONArray; }

class SaveGameManager
{
public:
	static void saveGame(Game &game);
	static void loadGame(Game *game);
	static void addToAttachNeightbourList(Chamber *chamber, JSON::JSONArray *neighbourArr) { instance()._attachNeightbourList.insert(std::make_pair(chamber, neighbourArr)); }

private:
	std::map<Chamber*, JSON::JSONArray*> _attachNeightbourList;

	void attachNeightbours();

	static SaveGameManager &instance() {
		static SaveGameManager instance;
		return instance;
	}
};

