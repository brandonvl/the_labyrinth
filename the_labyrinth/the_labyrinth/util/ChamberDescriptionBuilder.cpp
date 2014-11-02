#include "ChamberDescriptionBuilder.h"
#include "model\Chamber.h"
#include "model\enums.h"

#include <sstream>

ChamberDescriptionBuilder::ChamberDescriptionBuilder()
{
}


ChamberDescriptionBuilder::~ChamberDescriptionBuilder()
{
}

std::string ChamberDescriptionBuilder::getDescription(Chamber &chamber) {

	std::stringstream stream;

	stream << "You're in a ";
	stream << chamberSizeNames.at(chamber.getSize()) << " ";
	stream << chamberStateNames.at(chamber.getState()) << " room";
	if (chamber.getInventory() == ChamberInventory::EMPTY)
		stream << ". The room is completely empty and is ";
	else {
		stream << ", with a ";
		stream << chamberInventoryNames.at(chamber.getInventory()) << " in the ";
		stream << chamberInventoryPositionNames.at(chamber.getInventoryPosition()) << ". The room is ";
	}

	stream << "illuminated by a ";
	stream << chamberLightningNames.at(chamber.getLightning()) << ".";

	return stream.str();
}