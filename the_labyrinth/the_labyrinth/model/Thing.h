#pragma once

#include <string>

class Thing
{
public:
	Thing();
	virtual ~Thing();
	std::string getName();
private:
	std::string _name;
};

