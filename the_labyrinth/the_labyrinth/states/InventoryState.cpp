#include "InventoryState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "model\Inventory.h"
#include "model\Item.h"
#include "ExploreState.h"

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

	std::cout << "Inventory" << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;

	Inventory *inventory = _player->getInventory();

	if (inventory != nullptr && inventory->getItemCount() > 0) {

		for (auto item : inventory->getItems()) {
			std::cout << item.second << "x " << item.first->getName() << std::endl;
		}
	}
	else {
		std::cout << "There are no items in your inventory.";
	}

	std::cout << std::endl << std::endl;
	std::cout << "Press any key to exit...";
	
	std::cin.get();
	doOption();
}

void InventoryState::displayInfo()
{

}

void InventoryState::displayOptions()
{

}

void InventoryState::doOption() 
{
	system("cls");
	changeState(ExploreState::instance());
}