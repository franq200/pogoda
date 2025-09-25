#include "WeatherApp.h"
#include "IWeatherIniReader.h"
#include "ILogger.h"
#include "IHttpPoller.h"

WeatherApp::WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::shared_ptr<ILogger> logger, std::unique_ptr<ITimer> timer)
	: poller_(std::move(poller)), iniReader_(std::move(iniReader)), logger_(std::move(logger)), timer_(std::move(timer))
{
	cities_ = iniReader_->ReadCities();
	LogCities();
	BuildUrls();
}

void WeatherApp::Run()
{
	while (true)
	{
		//if (timer_->ShouldTick())
		{
			PollAllCities();
		}
	}
}

void WeatherApp::PollAllCities()
{
	for (const auto& url : urls_)
	{
		poller_->Poll(url);
	}
}

void WeatherApp::BuildUrls()
{
	urls_.clear();
	urls_.reserve(cities_.size());

	std::string baseUrl = "https://wttr.in/";
	std::string format = "?format=j1";

	for (const auto& city : cities_)
	{
		urls_.push_back(baseUrl + city + format);
	}
}

void WeatherApp::LogCities() const
{
	if (cities_.empty())
	{
		logger_->LogCriticalError("Brak miast do monitorowania. SprawdŸ plik config.ini.");
	}
	else
	{
		std::string message = "Wczytano miasta do monitorowania:";
		for (const auto& city : cities_)
		{
			message += "\n - " + city;
		}
		logger_->LogInfo(message);
	}
}
