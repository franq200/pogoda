#pragma once
#include <string>
#include <vector>
#include "IDataParser.h"

struct PollResult;

class IHttpPoller
{
public:
	IHttpPoller() = default;
	virtual ~IHttpPoller() = default;
	virtual PollResult Poll(const std::string& url) = 0;
};

