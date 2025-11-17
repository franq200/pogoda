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

WeatherApp::WeatherApp(std::unique_ptr<IHttpPoller> weatherPoller, std::unique_ptr<IHttpPoller> currencyPoller, std::unique_ptr<IIniReader> iniReader, std::shared_ptr<ILogger> logger, std::shared_ptr<IDatabaseEngine> databaseEngine)
	: iniReader_(std::move(iniReader)), logger_(std::move(logger))
{
	std::vector<std::string> cities = iniReader_->GetValues("Weather", "City");
	std::vector<std::string> codes = iniReader_->GetValues("Currency", "Code");
	std::string period = iniReader_->GetValue("Currency", "Period");
	std::string historyDays = iniReader_->GetValue("Currency", "HistoryDays");

	LogCities(cities);
	databaseEngine->connect("pogoda.db");
	InitDatabase(databaseEngine.get(), cities);
	StartTasks(std::move(weatherPoller), std::move(currencyPoller), std::move(databaseEngine), cities, codes, period, historyDays);
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

void WeatherApp::StartTasks(std::unique_ptr<IHttpPoller> weatherPoller, std::unique_ptr<IHttpPoller> currencyPoller, std::shared_ptr<IDatabaseEngine> databaseEngine,
	const std::vector<std::string>& cities, const std::vector<std::string>& codes, const std::string& period, const std::string& historyDays)
{
	tasks_.clear();
	tasks_.emplace_back(std::make_unique<LoggingTask>(std::make_unique<Timer>(10), logger_));
	tasks_.emplace_back(std::make_unique<WeatherTask>(cities, std::move(weatherPoller), std::make_unique<Timer>(5), databaseEngine));
	tasks_.emplace_back(std::make_unique<CurrencyTask>(codes, std::make_unique<Timer>(std::stoull(period)), historyDays, databaseEngine, std::move(currencyPoller)));
	for (auto& task : tasks_)
	{
		task->Start();
	}
}

void WeatherApp::LogCities(const std::vector<std::string>& cities) const
{
	if (cities.empty())
	{
		logger_->LogCriticalError("Brak miast do monitorowania. SprawdŸ plik config.ini.");
	}
	else
	{
		std::string message = "Wczytano miasta do monitorowania:";
		for (const auto& city : cities)
		{
			message += "\n - " + city;
		}
		logger_->LogInfo(message);
	}
}

void WeatherApp::InitDatabase(IDatabaseEngine* databaseEngine, const std::vector<std::string>& cities) const
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

	for (const auto& city : cities)
	{
		std::string query =
			"INSERT INTO Location (Name) "
			"SELECT '" + city + "' "
			"WHERE NOT EXISTS (SELECT 1 FROM Location WHERE Name = '" + city + "');";

		databaseEngine->executeQuery(query);
	}
}
