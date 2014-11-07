#include "IntroState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "ExploreState.h"
#include "util\SaveGameManager.h"

void IntroState::init(Game &game)
{
	_game = &game;
	std::cout << "===============================================" << std::endl;
	std::cout << "          Welcome to The Labyrinth.            " << std::endl;
	std::cout << "===============================================" << std::endl;
	std::cout << std::endl;

}

void IntroState::cleanUp()
{
	_game = nullptr;
}

void IntroState::update()
{
	displayInfo();
	displayOptions();
	doOption();
}

void IntroState::displayInfo()
{

}

void IntroState::displayOptions()
{
	std::cout << "Options: [new|load|quit]" << std::endl;
	std::cout << "You choose: ";
	std::getline(std::cin, _chosenOption);
}

void IntroState::doOption()
{
	if (_chosenOption == "new") {
		Player *player = new Player();
		std::string playerName;
		std::cout << "Enter your name: ";
		std::getline(std::cin, playerName);
		std::cout << "Excellent choice, " << playerName << ". Press any key to start the game" << std::endl;
		std::cin.get();
		system("cls");
		player->setName(playerName);
		_game->createDungeon(*player);
		changeState(ExploreState::instance());
	}
	else if (_chosenOption == "load") {
		try{
			SaveGameManager::loadGame(_game);
			changeState(ExploreState::instance());
		}
		catch (...) {
			std::cout << "Cannot load file...";
			std::cin.get();
		}
	}
	else if (_chosenOption == "quit") {
		doOptionQuit();
	}
	else
	{
		std::cout << "Invalid choice." << std::endl << std::endl;
	}
}

void IntroState::doOptionNew()
{

}