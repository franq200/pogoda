#pragma once
#include <string>
#include <vector>
#include "IDataParser.h"

class IHttpPoller
{
public:
	IHttpPoller(const std::string& url);
	virtual ~IHttpPoller() = default;
protected:
	std::string url_;
	virtual void Poll() = 0;
};

