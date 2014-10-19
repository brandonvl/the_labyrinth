#pragma once

#include <vector>

class Chamber;
struct ChamberEncap;

class Floor
{
public:
	Floor();
	virtual ~Floor();
	void createFloor(const int &size, const int &minLevel, const int &maxLevel);
private:
	Chamber *_start;
	Chamber *_end;
	std::vector<std::vector<Chamber*>> _chambers;
	Chamber &generateChamber(const int &minLevel, const int &maxLevel);
	void createMaze(const int &size);
	void connectChambers(ChamberEncap &chamberOne, ChamberEncap &chamberTwo);
	void findSuitableChamber(const int &size, const int &x, const int &y, std::vector<ChamberEncap> &suitableChambers);
	void checkChamberValid(const int &x, const int &y, std::vector<ChamberEncap> &suitableChambers);

};

