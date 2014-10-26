#include "ExploreState.h"
#include "model\Game.h"
#include "model\Dungeon.h"
#include "model\Floor.h"
#include "model\Chamber.h"


int tempCounter = 0;

void ExploreState::init(Game &game)
{
	_game = &game;
}

void ExploreState::cleanUp()
{
	_game = nullptr;
}

void ExploreState::update()
{
	tempCounter++;

	if (tempCounter == 1)
		showMap();

	if (tempCounter > 10)
		_game->stop();
}

void ExploreState::displayInfo()
{

}

void ExploreState::displayOptions()
{

}

void ExploreState::doOption()
{

}

void ExploreState::showMap()
{
	Dungeon *dungeon = &_game->getDungeon();
	Floor *currentFloor = _game->getDungeon().getCurrentFloor();

	if (currentFloor != nullptr) {
		std::vector<std::vector<Chamber*>> chambers = currentFloor->getChambers();

		for (auto row : chambers)
		{
			for (Chamber *cham : row)
			{
				std::string chamber;

				//if (cham->isVisited())
				
				if (cham == &dungeon->getDungeonStart()) {
					chamber = "S";
				}
				else if (cham == &dungeon->getDungeonEnd()) {
					chamber = "E";
				}
				else if (cham->hasNeighbour(Direction::UPSTAIRS)) {
					chamber = "U";
				}
				else if (cham->hasNeighbour(Direction::DOWNSTAIRS)) {
					chamber = "D";
				}
				else {
					chamber = "N";
				}

				if (cham->hasNeighbour(Direction::EAST)) {
					chamber += "-";
				}
				else
				{
					chamber += " ";
				}

				std::cout << chamber.c_str();
			}
			std::cout << std::endl;

			for (Chamber *cham : row)
			{
				if (cham->hasNeighbour(Direction::SOUTH)) {
					std::cout << "| ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
		/*
		std::cout << "==================================" << std::endl;
		for (auto row : chambers)
		{
			for (Chamber *cham : row)
			{
				std::unordered_map<Direction, Chamber*> *neighbours = cham->getNeighbours();

				for (auto item : *neighbours)
				{
					std::cout << "Direction: " << static_cast<int>(item.first) << ", Chamber: " << item.second << std::endl;
				}
				std::cout << "==== end chamber ==" << std::endl;
			}

			std::cout << "==== end row ==" << std::endl;
		}*/
	}

}