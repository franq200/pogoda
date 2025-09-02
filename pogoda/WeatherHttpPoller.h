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

class WeatherHttpPoller : public IHttpPoller
{
public:
	WeatherHttpPoller(const std::string& url, IDataParser<WeatherData>& dataParser);
	void Poll() override;
private:
	WeatherData response_;
	IDataParser<WeatherData>& dataParser_;
	std::vector<std::string> cities_;
};


