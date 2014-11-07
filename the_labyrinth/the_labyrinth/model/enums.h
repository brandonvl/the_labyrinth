#pragma once

#include <string>
#include <map>


enum class Direction
{
	NORTH = 1, SOUTH = 2, WEST = 3, EAST = 4, UPSTAIRS = 5, DOWNSTAIRS = 6, INVALID = 7
};

const std::map<const Direction, const std::string> directionNames{
	{ Direction::NORTH, "north" },
	{ Direction::EAST, "east" },
	{ Direction::WEST, "west", },
	{ Direction::SOUTH, "south" },
	{ Direction::UPSTAIRS, "up" },
	{ Direction::DOWNSTAIRS, "down" } };

enum class ItemType { HEALTH, MAXHEALTH, LEVEL, EXPERIENCE, DEFENCE, ATTACK, PERCEPTION, ATTACKVALUE };

const std::map<const std::string, const ItemType> keyItemTypeMap{
	{ "health", ItemType::HEALTH },
	{ "maxHealth", ItemType::MAXHEALTH },
	{ "level", ItemType::LEVEL },
	{ "experience", ItemType::EXPERIENCE },
	{ "defence", ItemType::DEFENCE },
	{ "attack", ItemType::ATTACK },
	{ "perception", ItemType::PERCEPTION },
	{ "attackValue", ItemType::ATTACKVALUE }
};
