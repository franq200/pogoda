#include <memory>
#include <csignal>

#include "WeatherApp.h"
#include "WeatherHttpPoller.h"
#include "WeatherIniReader.h"
#include "Logger.h"
#include "JsonDataParser.h"
#include "Timer.h"
#include "SQLiteEngine.h"
#include "CurrencyPoller.h"

#include <sqlite3.h>
#include <iostream>

void OnExit(int signum)
{
	auto logger = Logger::GetInstance();
	logger->LogInfo("Application is terminating...");
	exit(signum);
}

int main()
{
	std::signal(SIGINT, OnExit);
	std::signal(SIGTERM, OnExit);
	auto logger = Logger::GetInstance();
	WeatherApp app(std::make_unique<WeatherHttpPoller>(std::make_unique<JsonDataParser<WeatherData>>()), std::make_unique<CurrencyPoller>(std::make_unique<JsonDataParser<CurrencyResponse>>()), std::make_unique<DataCollectorIniReader>("../config.ini"), logger, std::make_unique<SQLiteEngine>());
	app.Run();
	return 0;
}