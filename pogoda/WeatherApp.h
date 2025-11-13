#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ITask.h"

class ITimer;
class IHttpPoller;
class IIniReader;
class ILogger;
class IDatabaseEngine;

class WeatherApp
{
public:
	WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IIniReader> iniReader, std::shared_ptr<ILogger> logger, std::unique_ptr<IDatabaseEngine> databaseEngine);
	~WeatherApp();
	void Run();
	void OnExit();
private:
	void StartTasks(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IDatabaseEngine> databaseEngine, 
		const std::vector<std::string>& cities_, const std::vector<std::string>& codes, const std::string& period, const std::string& historyDays);
	void LogCities(const std::vector<std::string>& citites) const;
	void InitDatabase(IDatabaseEngine* databaseEngine, const std::vector<std::string>& cities) const;

	std::unique_ptr<IIniReader> iniReader_;
	std::shared_ptr<ILogger> logger_;
	std::vector<std::unique_ptr<ITask>> tasks_;
	bool keepRunning_ = true;
};

