#include "WeatherIniReader.h"
#include <iostream>
#include <sstream>
#include "Logger.h"

WeatherIniReader::WeatherIniReader(const std::string& path):
	reader_(path)
{
	if (reader_.ParseError() < 0) 
	{
		auto logger = Logger::GetInstance();
		logger->LogCriticalError("Nie mogê wczytaæ pliku " + path);
	}
}

std::vector<std::string> WeatherIniReader::ReadCities() const
{
	std::vector<std::string> cities;
	std::string rawCities =	reader_.GetString("", "city", "");
	std::string city;
	std::istringstream ssCities(rawCities);
	while (std::getline(ssCities, city, '\n'))
	{
		cities.push_back(city);
	}
	return cities;
}
