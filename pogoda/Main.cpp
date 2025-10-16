#include <memory>
#include <csignal>

#include "WeatherApp.h"
#include "WeatherHttpPoller.h"
#include "WeatherIniReader.h"
#include "Logger.h"
#include "JsonDataParser.h"
#include "Timer.h"

#include <sqlite3.h>
#include <iostream>

int test() {
	sqlite3* db;
	if (sqlite3_open("test.db", &db)) {
		std::cerr << "Nie mo�na otworzy� bazy danych: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	std::cout << "Baza danych otwarta pomy�lnie!" << std::endl;
	sqlite3_close(db);
	return 0;
}

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
	test();
	auto logger = Logger::GetInstance();
	WeatherApp app(std::make_unique<WeatherHttpPoller>(std::make_unique<JsonDataParser<WeatherData>>()), std::make_unique<WeatherIniReader>("../config.ini"), logger);
	app.Run();
	return 0;
}