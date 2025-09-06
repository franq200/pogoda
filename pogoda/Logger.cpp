#include "Logger.h"
#include <iostream>
#include <chrono>
#include <string>
#include <iostream>
#include <filesystem>

std::shared_ptr<Logger> Logger::instance_;
std::ofstream Logger::logFile_;

Logger::~Logger()
{
	if (logFile_.is_open())
	{
		LogInfo("Logging ended.");
		logFile_.close();
	}
}

CurrentTime Logger::GetCurrentTime() const
{
	CurrentTime currentTime;
	auto currentTimeChrono = std::chrono::system_clock::now();
	auto currentDateChrono = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono));

	currentTime.year = std::to_string(static_cast<int>(currentDateChrono.year()));
	currentTime.month = std::to_string(static_cast<unsigned>(currentDateChrono.month()));
	currentTime.day = std::to_string(static_cast<unsigned>(currentDateChrono.day()));
	currentTime.hour = std::to_string(std::chrono::time_point_cast<std::chrono::hours>(currentTimeChrono).time_since_epoch().count() % 24);
	currentTime.minute = std::to_string(std::chrono::time_point_cast<std::chrono::minutes>(currentTimeChrono).time_since_epoch().count() % 60);
	currentTime.second = std::to_string(std::chrono::time_point_cast<std::chrono::seconds>(currentTimeChrono).time_since_epoch().count() % 60);
	currentTime.timeSinceEpoch = std::to_string(currentTimeChrono.time_since_epoch().count());
	return currentTime;
}

Logger::Logger()
{
	CurrentTime currentTime = GetCurrentTime();

	std::string folderPath = "log/" + currentTime.year + "/" + currentTime.month + "/" + currentTime.day;
	std::filesystem::create_directories(folderPath);
	
	std::string filename = folderPath + "/" + currentTime.timeSinceEpoch + ".txt";
	logFile_.open(filename, std::ios::app);

	LogInfo("Logging started...");
}

void Logger::Log(const std::string& message, LogLevel logLevel) const
{
	switch (logLevel)
	{
	case LogLevel::Error:
		logFile_ << "[E]" << message << std::endl; // current time rok miesi¹c dzieñ godzina minuta sekunda milisekunda
		break;
	case LogLevel::Warning:
		logFile_ << "[W] " << message << std::endl;
		break;
	case LogLevel::Info:
		logFile_ << "[I]" << message << std::endl;
		break;
	default:
		logFile_ << "UNKNOWN LOG LEVEL: " << message << std::endl;
		break;
	}
}
