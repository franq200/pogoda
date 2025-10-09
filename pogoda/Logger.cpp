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

void Logger::LogCollectedLogs()
{
	for (const auto& log : collectedLogs_)
	{
		if (logFile_.is_open())
		{
			logFile_ << log << std::endl;
		}
		else
		{
			std::cerr << "Log file is not open. Cannot write log: " << log << std::endl;
		}
	}
	collectedLogs_.clear();
}

Logger::Logger()
{
	CreateLogFile();
}

void Logger::CreateLogFile()
{
	LastLogTime_ = TimeProvider::GetCurrentDay();
	if (logFile_.is_open())
	{
		logFile_.close();
	}
	CurrentTime currentTime = TimeProvider::GetCurrentTime();
	std::string folderPath = "log/" + currentTime.year + "/" + currentTime.month + "/" + currentTime.day;
	std::filesystem::create_directories(folderPath);
	std::string filename = folderPath + "/" + currentTime.millisecondsSinceEpoch + ".txt";
	logFile_.open(filename, std::ios::app);
	LogInfo("Logging started...");
}

void Logger::Log(const std::string& message, LogLevel logLevel)
{
	if (LastLogTime_ != TimeProvider::GetCurrentDay())
	{
		CreateLogFile();
	}

	std::string currentTimeString = TimeProvider::GetCurrentTimeString();
	switch (logLevel)
	{
	case LogLevel::Error:
		collectedLogs_.push_back("[E] " + currentTimeString + ": " + message);
		break;
	case LogLevel::Warning:
		collectedLogs_.push_back("[W] " + currentTimeString + ": " + message);
		break;
	case LogLevel::Info:
		collectedLogs_.push_back("[I] " + currentTimeString + ": " + message);
		break;
	default:
		collectedLogs_.push_back("UNKNOWN LOG LEVEL: " + currentTimeString + ": " + message);
		break;
	}
}