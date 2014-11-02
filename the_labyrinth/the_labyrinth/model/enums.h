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

enum class ChamberSize { SMALL = 0, MEDIUM = 1, LARGE = 2 };

const std::map<const ChamberSize, const std::string> chamberSizeNames{
	{ ChamberSize::SMALL, "small" },
	{ ChamberSize::MEDIUM, "medium" },
	{ ChamberSize::LARGE, "large", } };

enum class ChamberState { CLEAN = 0, DIRTY = 1 };

const std::map<const ChamberState, const std::string> chamberStateNames{
	{ ChamberState::CLEAN, "clean" },
	{ ChamberState::DIRTY, "dirty" } };

enum class ChamberLightning { CANDLE = 0, TORCH = 1, FIREPLACE = 2 };

const std::map<const ChamberLightning, const std::string> chamberLightningNames{
	{ ChamberLightning::CANDLE, "candle" },
	{ ChamberLightning::TORCH, "torch" },
	{ ChamberLightning::FIREPLACE, "fireplace", } };

enum class ChamberInventory { EMPTY = 0, BED = 1, TABLE = 2 };

const std::map<const ChamberInventory, const std::string> chamberInventoryNames{
	{ ChamberInventory::BED, "bed" },
	{ ChamberInventory::TABLE, "table" } };

enum class ChamberInventoryPosition { CORNER = 0, CENTER = 1 };

const std::map<const ChamberInventoryPosition, const std::string> chamberInventoryPositionNames{
	{ ChamberInventoryPosition::CORNER, "corner" },
	{ ChamberInventoryPosition::CENTER, "center" } };