#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ITask.h"

class ITimer;
class IHttpPoller;
class IWeatherIniReader;
class ILogger;
class IDatabaseEngine;

class WeatherApp
{
public:
	WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::shared_ptr<ILogger> logger, std::unique_ptr<IDatabaseEngine> databaseEngine);
	~WeatherApp();
	void Run();
	void OnExit();
private:
	void StartTasks(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IDatabaseEngine> databaseEngine);
	std::vector < std::string> GetUrls();
	void LogCities() const;

	std::vector<std::string> cities_;
	std::unique_ptr<IWeatherIniReader> iniReader_;
	std::shared_ptr<ILogger> logger_;
	std::vector<std::unique_ptr<ITask>> tasks_;
	bool keepRunning_ = true;
};

