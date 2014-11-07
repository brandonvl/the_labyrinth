#include "InventoryState.h"
#include "model\Game.h"
#include "model\Player.h"
#include "model\Inventory.h"
#include "model\Item.h"
#include "ExploreState.h"
#include "FightState.h"
#include <algorithm>

void InventoryState::init(Game &game)
{
	_game = &game;
	_player = &game.getPlayer();
	system("cls");
}

void InventoryState::cleanUp()
{
	_game = nullptr;
	_fightStateSend = false;
}

void InventoryState::update()
{
	displayInfo();
	displayOptions();
	doOption();
}

void InventoryState::displayInfo()
{
	system("cls");

	std::cout << "Inventory" << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;

	Inventory *inventory = _player->getInventory();

	if (inventory != nullptr && inventory->getItemCount() > 0) {

		int index = 0;
		for (auto item : inventory->getItems()) {
			index++;
			std::cout << index << ". " << item.second << "x " << item.first->getName() << std::endl;
		}
	}
	else {
		std::cout << "There are no items in your inventory.";
	}

	std::cout << std::endl << std::endl;
}

void InventoryState::displayOptions()
{
	if (_player->getInventory()->getItemCount() > 0) {
		std::cout << "Options: [|use|back]" << std::endl;
		std::cout << "Your choice: ";
		std::getline(std::cin, _chosenOption);
	}
}

void InventoryState::doOptionBack()
{
	if (!_fightStateSend)
		changeState(ExploreState::instance());
	else
		changeState(FightState::instance());
}

std::string InventoryState::getItemTypeText(Item &item)
{
	auto lamba = [&item](const std::pair<std::string, ItemType> value){ return value.second == item.getType(); };
	auto keyValue = std::find_if(keyItemTypeMap.begin(), keyItemTypeMap.end(), lamba);

	if (keyValue != keyItemTypeMap.end())
		return (*keyValue).first;
	else
		return "??unknown??";
}

void InventoryState::doOptionUse()
{
	bool didUseItem = false;
	int itemSlot;
	std::string userInput = "";

	do
	{
		std::cout << "Use item: ";
		std::getline(std::cin, userInput);

		try
		{
			itemSlot = std::stoi(userInput);

			if (_player->getInventory()->getItemCount() < itemSlot || itemSlot < 1) {
				std::cout << "Invalid item slot. Pick a item slot number (the number before the names)." << std::endl;
			}
			else
			{
				Item *item;

				auto it = _player->getInventory()->getItems().begin();
				std::advance(it, itemSlot - 1);
				item = it->first;

				
				std::cout << "Using " << item->getName() << " has increased your " << getItemTypeText(*item) << " by " << item->getAmount() << std::endl;
				

				if (item->getType() == ItemType::EXPERIENCE) {
					_player->getInventory()->useItem(*item);
					if (_player->isLevelUp()) {
						int levelBefore = _player->getLevel();
						_player->doLevelUp();
						std::cout << "You have leveled up from " << levelBefore << " to " << _player->getLevel() << "." << std::endl;
						std::cout << "Your stats have increased." << std::endl;
					}
				}
				else
					_player->getInventory()->useItem(*item);

				didUseItem = true;

			}
		}
		catch (std::invalid_argument)
		{
			std::cout << "Invalid item slot. Pick a item slot number (the number before the names)." << std::endl;
		}
		catch (std::out_of_range)
		{
			std::cout << "Invalid item slot. Pick a item slot number (the number before the names)." << std::endl;
		}

	} while (!didUseItem);

	std::cout << "Press any key to continue...";
	std::cin.get();
	doOptionBack();
}

void InventoryState::doOption() 
{
	if (_player->getInventory()->getItemCount() > 0) {

		if (_chosenOption == "use") {
			doOptionUse();
		}
		else if (_chosenOption == "back") {
			doOptionBack();
		}
		else
		{
			std::cout << "Invalid choice. You lost a turn." << std::endl;
			std::cout << "Press any key to continue..";
			std::cin.get();
		}
	}
	else
	{
		doOptionBack();
	}
	
}