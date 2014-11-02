#include "IntroState.h"
#include "model\Game.h"


void IntroState::init(Game &game)
{
	_game = &game;
	std::cout << "===================================" << std::endl;
	std::cout << "Welcome to The Labyrinth. Reach" << std::endl;
	std::cout << "===================================" << std::endl;
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

	std::cout << "You choose: ";
	std::getline(std::cin, _chosenOption);
}

void IntroState::doOption()
{
	doOptionQuit();
}

void IntroState::doOptionQuit()
{
	_game->stop();
}

void IntroState::doOptionPlay()
{

}