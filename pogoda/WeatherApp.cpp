#include "WeatherApp.h"
#include "IWeatherIniReader.h"
#include "ILogger.h"
#include "IHttpPoller.h"
#include "Timer.h"
#include "ITimer.h"
#include "ITask.h"
#include "LoggingTask.h"
#include "WeatherTask.h"

WeatherApp::WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IWeatherIniReader> iniReader, std::shared_ptr<ILogger> logger)
	: poller_(std::move(poller)), iniReader_(std::move(iniReader)), logger_(std::move(logger))
{
	cities_ = iniReader_->ReadCities();
	LogCities();
	StartTasks();
}

WeatherApp::~WeatherApp()
{
	OnExit();
	for (auto& task : tasks_)
	{
		task->Join();
	}
}

void WeatherApp::Run()
{
	while (keepRunning_)
	{};
	for (auto& task : tasks_)
	{
		task->Join();
	}
}

void WeatherApp::OnExit()
{
	for (auto& task : tasks_)
	{
		task->Stop();
	}
	keepRunning_ = false;
}

void WeatherApp::StartTasks()
{
	tasks_.clear();
	tasks_.emplace_back(std::make_unique<LoggingTask>(std::make_unique<Timer>(10)));
	tasks_.emplace_back(std::make_unique<WeatherTask>(GetUrls(), std::move(poller_), std::make_unique<Timer>(5)));
	for (auto& task : tasks_)
	{
		task->Start();
	}
}

std::vector<std::string> WeatherApp::GetUrls()
{
	std::vector<std::string> urls;
	urls.clear();
	urls.reserve(cities_.size());

	std::string baseUrl = "https://wttr.in/";
	std::string format = "?format=j1";

	for (const auto& city : cities_)
	{
		urls.push_back(baseUrl + city + format);
	}
	return urls;
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
