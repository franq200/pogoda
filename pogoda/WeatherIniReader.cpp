#include "WeatherIniReader.h"
#include <iostream>
#include <sstream>

WeatherIniReader::WeatherIniReader(const std::string& path):
	reader_(path)
{
	if (reader_.ParseError() < 0) 
	{
		std::cerr << "Nie mogê wczytaæ pliku " << path << "\n";
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
