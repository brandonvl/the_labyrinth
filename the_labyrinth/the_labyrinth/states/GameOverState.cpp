#include "GameOverState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "IntroState.h"

void GameOverState::init(Game &game)
{
	_game = &game;
	_player = &game.getPlayer();
}

void GameOverState::cleanUp()
{
	_game = nullptr;
}

void GameOverState::update()
{
	system("cls");

	std::cout << "The Hero " << _player->getName() << " ";
	
	if (_player->hasWon() > 0) std::cout << "has won the epic battle of The Labyrinth";
	else std::cout << "has been defeated";
	
	std::cout << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "STATS";
	std::cout << "---------------------------------" << std::endl << std::endl;

	std::cout << "Experience: " << _player->getExperience();
	std::cout << "Health: " << _player->getHealth();
	std::cout << "Level: " << _player->getLevel();

	std::cout << std::endl << std::endl;

	std::cout << "Press R to play again or any key to quit...";

	char ch = 0;	
	std::cin.get(ch);

	if (ch == 'r' || ch == 'R') changeState(IntroState::instance());
	else _game->stop();
}

void GameOverState::displayInfo()
{
}

void GameOverState::displayOptions()
{
}

void GameOverState::doOption()
{
}