#pragma once
#include <string>
#include <vector>
#include "IDataParser.h"

class IHttpPoller
{
public:
	IHttpPoller(const std::string& url);
	virtual ~IHttpPoller() = default;
	virtual void Poll() = 0;
protected:
	std::string url_;
};

