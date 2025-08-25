#pragma once
#include <vector>
#include <string>
#include <memory>

class IHttpPoller;
class IWeatherIniReader;
class ILogger;

class WeatherApp
{
public:
	WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::unique_ptr<ILogger> logger, int intervalSeconds, std::vector<std::string>& cities);
	void Run();
private:
	std::vector<std::string> cities_;
	int intervalSeconds_;
	std::unique_ptr<IHttpPoller> poller_;
	std::unique_ptr<IWeatherIniReader> iniReader_;
	std::unique_ptr<ILogger> logger_;
};

