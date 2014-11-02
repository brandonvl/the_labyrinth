#pragma once
#include <string>

class Chamber;

class ChamberDescriptionBuilder
{
public:
	ChamberDescriptionBuilder();
	virtual ~ChamberDescriptionBuilder();

	static std::string getDescription(Chamber &chamber);
};

