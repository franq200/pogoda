#pragma once
#include "ITask.h"
#include <vector>
#include <string>

class IHttpPoller;
class ITimer;
class IDatabaseEngine;

class WeatherTask : public ITask
{
public:
	WeatherTask(std::vector<std::string> urls, std::unique_ptr<IHttpPoller> poller, std::unique_ptr<ITimer> timer, std::unique_ptr<IDatabaseEngine> databaseEngine);
protected:
	void Execute() override;
private:
	std::unique_ptr<ITimer> timer_;
	const std::vector<std::string> urls_;
	std::unique_ptr<IHttpPoller> poller_;
	std::unique_ptr<IDatabaseEngine> databaseEngine_;
};

