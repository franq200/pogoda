#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iostream>
#include <filesystem>

std::shared_ptr<Logger> Logger::instance_;
std::ofstream Logger::logFile_;

namespace {
	CurrentTime GetCurrentTime()
	{
		CurrentTime currentTime;
		auto currentTimeChrono = std::chrono::system_clock::now();
		auto currentDateChrono = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTimeChrono));

		currentTime.year = std::to_string(static_cast<int>(currentDateChrono.year()));
		currentTime.month = std::to_string(static_cast<unsigned int>(currentDateChrono.month()));
		currentTime.day = std::to_string(static_cast<unsigned int>(currentDateChrono.day()));
		currentTime.hour = std::to_string(std::chrono::time_point_cast<std::chrono::hours>(currentTimeChrono).time_since_epoch().count() % 24);
		currentTime.minute = std::to_string(std::chrono::time_point_cast<std::chrono::minutes>(currentTimeChrono).time_since_epoch().count() % 60);
		currentTime.second = std::to_string(std::chrono::time_point_cast<std::chrono::seconds>(currentTimeChrono).time_since_epoch().count() % 60);

		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeChrono.time_since_epoch()).count();
		currentTime.millisecond = std::to_string(ms%1000);
		currentTime.millisecondsSinceEpoch = std::to_string(ms);
		return currentTime;
	}; // dodac funkcje get current day/month/year/second...

	std::string GetCurrentTimeString()
	{
		CurrentTime currentTime = GetCurrentTime();
		return currentTime.year + "-" + currentTime.month + "-" + currentTime.day + " " +
			currentTime.hour + ":" + currentTime.minute + ":" + currentTime.second + "." + currentTime.millisecond;
	};
}

Logger::~Logger()
{
	if (logFile_.is_open())
	{
		LogInfo("Logging ended.");
		logFile_.close();
	}
}

Logger::Logger()
{
	CreateLogFile();
}

void Logger::CreateLogFile()
{
	LastLogTime_ = GetCurrentTime();
	if (logFile_.is_open())
	{
		logFile_.close();
	}
	CurrentTime currentTime = GetCurrentTime();
	std::string folderPath = "log/" + currentTime.year + "/" + currentTime.month + "/" + currentTime.day;
	std::filesystem::create_directories(folderPath);
	std::string filename = folderPath + "/" + currentTime.millisecondsSinceEpoch + ".txt";
	logFile_.open(filename, std::ios::app);
	LogInfo("Logging started...");
}

void Logger::Log(const std::string& message, LogLevel logLevel)
{
	if (LastLogTime_.day != GetCurrentTime().day)
	{
		CreateLogFile();
	}

	std::string currentTimeString = GetCurrentTimeString();
	switch (logLevel)
	{
	case LogLevel::Error:
		logFile_ << "[E] " << currentTimeString << ": " << message << std::endl;
		break;
	case LogLevel::Warning:
		logFile_ << "[W] " << currentTimeString << ": " << message << std::endl;
		break;
	case LogLevel::Info:
		logFile_ << "[I] " << currentTimeString << ": " << message << std::endl;
		break;
	default:
		logFile_ << "UNKNOWN LOG LEVEL: " << currentTimeString << ": " << message << std::endl;
		break;
	}
}