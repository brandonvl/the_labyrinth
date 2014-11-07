#pragma once
#include "JSONSerializable.h"
#include <string>

class Thing :
	public JSONSerializable
{
public:
	Thing();
	virtual ~Thing();
	std::string getName() { return _name; }
	void setName(const std::string &name) { _name = name; }
	virtual JSON::JSONElement &serialize(JSON::JSONElement *parent = nullptr) override = 0;
	void deserialize(JSON::JSONObject &element) override = 0;

private:
	std::string _name;
};

