#include "ILogger.h"
#include <stdexcept>

void ILogger::LogError(const std::string& message) const
{
	Log(message, LogLevel::Error);
}

void ILogger::LogWarning(const std::string& message) const
{
	Log(message, LogLevel::Warning);
}

void ILogger::LogInfo(const std::string& message) const
{
	Log(message, LogLevel::Info);
}

void ILogger::LogCriticalError(const std::string& message) const
{
	Log(message, LogLevel::Error);
	throw std::runtime_error(message);
}
