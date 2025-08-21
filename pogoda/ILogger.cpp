#include "ILogger.h"

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
