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
	WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::shared_ptr<ILogger> logger, std::unique_ptr<ITimer> timer);
	void Run();
private:
	void PollAllCities();
	void BuildUrls();
	void LogCities() const;

	std::vector<std::string> urls_;
	std::vector<std::string> cities_;
	std::unique_ptr<ITimer> timer_;
	std::unique_ptr<IHttpPoller> poller_;
	std::unique_ptr<IWeatherIniReader> iniReader_;
	std::shared_ptr<ILogger> logger_;
};

