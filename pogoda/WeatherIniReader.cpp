#include "WeatherIniReader.h"
#include <iostream>
#include <sstream>
#include "Logger.h"

DataCollectorIniReader::DataCollectorIniReader(const std::string& path):
	reader_(path)
{
	if (reader_.ParseError() < 0) 
	{
		auto logger = Logger::GetInstance();
		logger->LogCriticalError("Nie mogê wczytaæ pliku " + path); // Log critical error if file cannot be read
	}
}

std::vector<std::string> DataCollectorIniReader::GetValues(const std::string& section, const std::string& key) const
{
	std::vector<std::string> values;
	std::string rawValues =	reader_.GetString(section, key, "");
	std::string value;
	std::istringstream ssValues(rawValues);
	while (std::getline(ssValues, value, '\n'))
	{
		values.push_back(value);
	}
	return values;
}

std::string DataCollectorIniReader::GetValue(const std::string& section, const std::string& key) const
{
	return reader_.GetString(section, key, "");
}
