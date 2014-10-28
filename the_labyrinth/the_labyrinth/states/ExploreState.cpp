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

		std::cout << "Dungeon map:" << std::endl;
		for (auto row : chambers)
		{
			for (Chamber *cham : row)
			{
				showChamber(cham);
			}
			std::cout << std::endl;

			for (Chamber *cham : row)
			{
				if (cham->hasNeighbour(Direction::SOUTH) && (cham->isVisited() || cham->getNeighbour(Direction::SOUTH)->isVisited())) {
					std::cout << "| ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}

		showMapInfo();

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

void ExploreState::showChamber(Chamber *cham)
{
	std::string chamber;

	if (!cham->isVisited()) {
		chamber = ".";
	}
	else
	{
		if (cham == &_game->getDungeon().getDungeonStart()) {
			chamber = "S";
		}
		else if (cham == &_game->getDungeon().getDungeonEnd()) {
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
	}

	if (cham->hasNeighbour(Direction::EAST) && (cham->isVisited() || cham->getNeighbour(Direction::EAST)->isVisited())) {
		chamber += "-";
	}
	else
	{
		chamber += " ";
	}

	std::cout << chamber.c_str();
}

void ExploreState::showMapInfo()
{
	std::cout << "==============" << std::endl;
	std::cout << "|- = Passages" << std::endl;
	std::cout << "N  = Normal room" << std::endl;
	std::cout << "S  = Start location dungeon" << std::endl;
	std::cout << "E  = End location dungeon (boss)" << std::endl;
	std::cout << "U  = Move floor up" << std::endl;
	std::cout << "D  = Move floor down" << std::endl;
	std::cout << ".  = Not visited" << std::endl;
}