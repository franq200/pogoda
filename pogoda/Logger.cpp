#include <iostream>
#include <string>
#include <chrono>
#include <iostream>
#include <filesystem>
#include "TimeProvider.h"
#include "Logger.h"

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

Logger::Logger()
{
	CreateLogFile();
}

void Logger::CreateLogFile()
{
	LastLogTime_ = timeProvider_.GetCurrentDay();
	if (logFile_.is_open())
	{
		logFile_.close();
	}
	CurrentTime currentTime = timeProvider_.GetCurrentTime();
	std::string folderPath = "log/" + currentTime.year + "/" + currentTime.month + "/" + currentTime.day;
	std::filesystem::create_directories(folderPath);
	std::string filename = folderPath + "/" + currentTime.millisecondsSinceEpoch + ".txt";
	logFile_.open(filename, std::ios::app);
	LogInfo("Logging started...");
}

void Logger::Log(const std::string& message, LogLevel logLevel)
{
	if (LastLogTime_ != timeProvider_.GetCurrentDay())
	{
		CreateLogFile();
	}

	std::string currentTimeString = timeProvider_.GetCurrentTimeString();
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