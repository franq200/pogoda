#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IDataParser.h"


class IHttpPoller
{
public:
	struct PollResult
	{
	};

public:
	IHttpPoller() = default;
	virtual ~IHttpPoller() = default;
	virtual std::unique_ptr<PollResult> Poll(const std::string& url) = 0;
};

