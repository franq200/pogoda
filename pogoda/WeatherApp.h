#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Timer.h"

class IHttpPoller;
class IWeatherIniReader;
class ILogger;

class WeatherApp
{
public:
	WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::shared_ptr<ILogger> logger, int intervalSeconds);
	void Run();
private:
	std::vector<std::string> cities_;
	Timer timer_;
	std::unique_ptr<IHttpPoller> poller_;
	std::unique_ptr<IWeatherIniReader> iniReader_;
	std::shared_ptr<ILogger> logger_;
};

