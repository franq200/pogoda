#include "WeatherApp.h"
#include "IIniReader.h"
#include "ILogger.h"
#include "IHttpPoller.h"
#include "Timer.h"
#include "ITimer.h"
#include "ITask.h"
#include "LoggingTask.h"
#include "WeatherTask.h"
#include "CurrencyTask.h"
#include "IDatabaseEngine.h"

WeatherApp::WeatherApp(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IIniReader> iniReader, std::shared_ptr<ILogger> logger, std::unique_ptr<IDatabaseEngine> databaseEngine)
	: iniReader_(std::move(iniReader)), logger_(std::move(logger))
{
	cities_ = iniReader_->GetValues("Weather", "City");
	codes_ = iniReader_->GetValues("Currency", "Code");
	period_ = iniReader_->GetValue("Currency", "Period");
	historyDays = iniReader_->GetValue("Currency", "HistoryDays");

	LogCities();
	databaseEngine->connect("pogoda.db");
	InitDatabase(databaseEngine.get());
	StartTasks(std::move(poller), std::move(databaseEngine));
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

void WeatherApp::StartTasks(std::unique_ptr<IHttpPoller> poller, std::unique_ptr<IDatabaseEngine> databaseEngine)
{
	tasks_.clear();
	tasks_.emplace_back(std::make_unique<LoggingTask>(std::make_unique<Timer>(10), logger_));
	tasks_.emplace_back(std::make_unique<WeatherTask>(GetUrls(), std::move(poller), std::make_unique<Timer>(5), std::move(databaseEngine)));
	tasks_.emplace_back(std::make_unique<CurrencyTask>(codes_, std::make_unique<Timer>(period_), historyDays, std::move(databaseEngine), std::move(poller)));
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

void WeatherApp::InitDatabase(IDatabaseEngine* databaseEngine) const
{
	std::string createLocationTableQuery =
		"CREATE TABLE Location(Name TEXT PRIMARY KEY)";
	databaseEngine->executeQuery(createLocationTableQuery);

	std::string createWeatherDataTableQuery =
		R"(CREATE TABLE WeatherData
		(
			ID INTEGER PRIMARY KEY AUTOINCREMENT,
			Location TEXT NOT NULL,
			CurrentTime TEXT NOT NULL,
			Temperature REAL,
			Humidity REAL, WindSpeed,
			FOREIGN KEY(Location) REFERENCES Location(Name)
			))";
	databaseEngine->executeQuery(createWeatherDataTableQuery);

	for (const auto& city : cities_)
	{
		std::string query =
			"INSERT INTO Location (Name) "
			"SELECT '" + city + "' "
			"WHERE NOT EXISTS (SELECT 1 FROM Location WHERE Name = '" + city + "');";

		databaseEngine->executeQuery(query);
	}
}
