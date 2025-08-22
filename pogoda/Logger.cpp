#include "Logger.h"
#include <iostream>
#include <chrono>
#include <string>
#include <iostream>
#include <filesystem>

std::unique_ptr<Logger> Logger::instance_;
std::ofstream Logger::logFile_;

Logger::Logger()
{
	auto currentTime = std::chrono::system_clock::now();
	auto currentDate = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTime));

	std::string year = std::to_string(static_cast<int>(currentDate.year()));
	std::string month = std::to_string(static_cast<unsigned>(currentDate.month()));
	std::string day = std::to_string(static_cast<unsigned>(currentDate.day()));

	std::string folderPath = "log/" + year + "/" + month + "/" + day;
	std::filesystem::create_directories(folderPath);
	
	std::string filename = folderPath + "/" + std::to_string(currentTime.time_since_epoch().count()) + ".txt";
	logFile_.open(filename, std::ios::app);
}

void Logger::Log(const std::string& message, LogLevel logLevel) const
{
	switch (logLevel)
	{
	case LogLevel::Error:
		std::cerr << "ERROR: " << message << std::endl;
		break;
	case LogLevel::Warning:
		std::cerr << "WARNING: " << message << std::endl;
		break;
	case LogLevel::Info:
		std::cout << "INFO: " << message << std::endl;
		break;
	default:
		std::cerr << "UNKNOWN LOG LEVEL: " << message << std::endl;
		break;
	}
}
