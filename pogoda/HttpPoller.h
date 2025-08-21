#pragma once
#include <string>
#include "IHttpPoller.h"

class HttpPoller : public IHttpPoller
{
public:
	HttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser);
private:
	void Poll() override;
	WeatherData response_;
};


