#pragma once
#include <vector>
#include <string>
#include "WeatherHttpPoller.h"
#include "WeatherIniReader.h"
#include "Logger.h"

class WeatherApp
{
public:
	WeatherApp(const std::string& url, IDataParser<WeatherData>& dataParser, int intervalSeconds, std::vector<std::string>& cities);
	~WeatherApp() = default;
	void Run();
private:
	std::vector<std::string> cities_;
	int intervalSeconds_;
	WeatherHttpPoller poller_;
	WeatherIniReader iniReader_;
	Logger* logger_ = Logger::GetInstance();
};

