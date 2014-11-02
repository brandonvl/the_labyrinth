#pragma once
#include <random>
#include <map>
#include <string>

class RandomGenerator
{
public:
	static int random(const int min, const int max);

private:
	RandomGenerator();
	virtual ~RandomGenerator();
	std::uniform_int_distribution<int> &getOrCreateDist(const int min, const int max);
	static RandomGenerator &instance();
	
	std::random_device _dev;
	std::default_random_engine _dre;
	std::map<std::string, std::uniform_int_distribution<int>*> _distMap;
};

