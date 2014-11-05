#include "InventoryState.h"
#include "model\Game.h"
#include "model\Player.h"

void InventoryState::init(Game &game)
{
	_game = &game;
	_player = &game.getPlayer();
	system("cls");
}

void InventoryState::cleanUp()
{
	_game = nullptr;
}

void InventoryState::update()
{
	system("cls");

	std::cout << "Inventory";
	std::cout << std::endl << std::endl;
	
	std::cin.get();
}

void InventoryState::displayInfo()
{

}

void InventoryState::displayOptions()
{

}

void InventoryState::doOption() 
{

}