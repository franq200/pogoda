#pragma once
#include <string>
#include <vector>
#include "IDataParser.h"

class IHttpPoller
{
public:
	IHttpPoller() = default;
	virtual ~IHttpPoller() = default;
	virtual void Poll(const std::string& url) = 0;
};

