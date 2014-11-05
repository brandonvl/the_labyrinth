#include "RandomGenerator.h"
#include <random>
#include "model\Monster.h"

RandomGenerator::RandomGenerator() : _dre(_dev())
{
}

RandomGenerator::~RandomGenerator()
{
	for (auto p : _distMap) {
		delete p.second;
		p.second = nullptr;
	}
}

RandomGenerator &RandomGenerator::instance() {
	static RandomGenerator _instance;
	return _instance;
}

int RandomGenerator::random(int min, int max) {
	return instance().getOrCreateDist(min, max)(instance()._dre);
}

std::uniform_int_distribution<int> &RandomGenerator::getOrCreateDist(const int min, const int max) {
	std::string key = std::to_string(min) + "_" + std::to_string(max);
	if (!_distMap.count(key)) 
		_distMap.insert(std::make_pair(key, new std::uniform_int_distribution<int>(min, max)));
	return *_distMap[key];
}