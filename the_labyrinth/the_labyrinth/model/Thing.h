#pragma once

#include <string>

class Thing
{
public:
	Thing();
	virtual ~Thing();
	std::string getName() { return _name; }
	void setName(const std::string &name) { _name = name; }
private:
	std::string _name;
};

