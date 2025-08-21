#include "Logger.h"
#include <iostream>
#include <chrono>
#include <string>


Logger::Logger()
{
	std::string year, month, day;
	auto currentTime = std::chrono::system_clock::now();
	auto currentDate = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(currentTime));

	year = std::to_string(static_cast<int>(currentDate.year()));
	month = std::to_string(static_cast<unsigned>(currentDate.month()));
	day = std::to_string(static_cast<unsigned>(currentDate.day()));
	
	std::string filename = "log/" + year + "/" + month + "/" + day + "/" + std::to_string(currentTime.time_since_epoch().count()) + ".txt";// nazwa ma byæ time_s_e
	logFile_.open(filename, std::ios::app);
}

void Logger::Log(const std::string& message, LogLevel logLevel) const
{
	//rok miesiac dzien
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
