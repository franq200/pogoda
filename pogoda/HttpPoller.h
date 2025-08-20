#pragma once
#include <string>
#include "IHttpPoller.h"

struct WeatherData
{
	std::string location;
	std::string temperature;
	std::string humidity;
	std::string windSpeed;
};

class HttpPoller : public IHttpPoller
{
public:
	HttpPoller(const std::string& url, int intervalSeconds);
private:
	void Poll() override;
	WeatherData response_;
};


