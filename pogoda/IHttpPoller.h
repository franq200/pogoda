#pragma once
#include <string>
#include "IDataParser.h"

struct WeatherData
{
	std::string location;
	std::string temperature;
	std::string humidity;
	std::string windSpeed;
};

class IHttpPoller
{
public:
	IHttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser);
	virtual ~IHttpPoller() = default;
protected:
	std::string url_;
	int intervalSeconds_;
	IDataParser<WeatherData>& dataParser_;
	virtual void Poll() = 0;
};

