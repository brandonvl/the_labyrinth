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
	std::cout << "FINAL STATS" << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;

	std::cout << "Level: " << _player->getLevel() << std::endl;
	std::cout << "HP / MaxHP: " << _player->getHealth() << " / " << _player->getMaxHealth() << std::endl;
	std::cout << "AttackValue: " << _player->getAttackValue() << std::endl;
	std::cout << "Defense: " << _player->getDefense() << std::endl;
	std::cout << "Attack: " << _player->getAttack() << std::endl;
	std::cout << "Perception: " << _player->getPerception() << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Press any key to quit...";
	std::cin.get();
	_game->stop();
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