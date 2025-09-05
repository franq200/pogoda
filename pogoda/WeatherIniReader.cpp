#include "WeatherIniReader.h"
#include <INIReader.h>
#include <iostream>
#include <sstream>

std::vector<std::string> WeatherIniReader::ReadCities(const std::string& filename) const //zrobi� konstruktor ��by nie otwiera� ini kilka razy dla r�nych zmiennych typu cities frequency 
{
	INIReader reader(filename);
	if (reader.ParseError() < 0) 
	{
		std::cerr << "Nie mog� wczyta� pliku " << filename << "\n";
		return {};
	}

	std::vector<std::string> cities;
	std::string rawCities =	reader.GetString("", "city", "");
	std::string city;
	std::istringstream ssCities(rawCities);
	while (std::getline(ssCities, city, '\n'))
	{
		cities.push_back(city);
	}
	return cities;
}
