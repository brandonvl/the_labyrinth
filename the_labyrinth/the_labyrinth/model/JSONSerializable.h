#pragma once
#include <JSONParser.h>
class JSONSerializable
{
public:
	virtual JSON::JSONElement *serialize(JSON::JSONElement *parent = nullptr) = 0;
};

