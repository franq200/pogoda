#include "WeatherApp.h"
#include "IWeatherIniReader.h"
#include "ILogger.h"
#include "IHttpPoller.h"

WeatherApp::WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::unique_ptr<ILogger> logger, int intervalSeconds, std::vector<std::string>& cities)
	: poller_(std::move(poller)), iniReader_(std::move(iniReader)), logger_(std::move(logger)), timer_(intervalSeconds), cities_(cities)
{
}

void WeatherApp::Run()
{
	while (true)
	{
		if (timer_.ShouldTick())
		{
			poller_->Poll();
		}
	}
}
