#pragma once
class Game;

class SaveGameManager
{
public:
	SaveGameManager();
	virtual ~SaveGameManager();
	void saveGame(Game &game);
	Game *loadGame();
};

