#include "IniReader.h"
#include <INIReader.h>
#include <iostream>

std::vector<std::string> IniReader::ReadCities(const std::string& filename) const
{
	INIReader reader(filename);
	if (reader.ParseError() < 0) 
	{
		std::cerr << "Nie mogê wczytaæ pliku " << filename << "\n";
		return {};
	}

	std::vector<std::string> cities;
	for (const auto& key : reader.Keys(""))
	{
		if (key == "city")
		{
			cities.push_back(reader.Get("", key, ""));
		}
	}
	return cities;
}
