#pragma once
#include <string>

class IHttpPoller
{
public:
	IHttpPoller(const std::string& url, int intervalSeconds);
	virtual ~IHttpPoller() = default;
protected:
	std::string url_;
	int intervalSeconds_;
	virtual void Poll() = 0;
};

