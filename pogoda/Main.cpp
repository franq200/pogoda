#include <memory>
#include <csignal>

#include "WeatherApp.h"
#include "WeatherHttpPoller.h"
#include "WeatherIniReader.h"
#include "Logger.h"
#include "JsonDataParser.h"
#include "Timer.h"

void OnExit(int signum)
{
	auto logger = Logger::GetInstance();
	logger->LogInfo("Application is terminating...");
}

int main()
{
	std::signal(SIGINT, OnExit);
	std::signal(SIGTERM, OnExit);
	auto logger = Logger::GetInstance();
	WeatherApp app(std::make_unique<WeatherHttpPoller>(std::make_unique<JsonDataParser<WeatherData>>()), std::make_unique<WeatherIniReader>(), logger, std::make_unique<Timer>(5));
	app.Run();
	return 0;
}