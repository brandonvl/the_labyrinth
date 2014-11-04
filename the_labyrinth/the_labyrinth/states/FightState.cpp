#include "FightState.h"



void FightState::init(Game &game)
{
	_game = &game;
	system("cls");
}

void FightState::cleanUp()
{
	_game = nullptr;
}

void FightState::update()
{

}

void FightState::displayInfo()
{

}

void FightState::displayOptions()
{

}

void FightState::doOption()
{

}