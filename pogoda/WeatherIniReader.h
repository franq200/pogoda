#pragma once
#include "IWeatherIniReader.h"
#include <INIReader.h>

class WeatherIniReader : public IWeatherIniReader
{
public:
	WeatherIniReader(const std::string& path);
	std::vector<std::string> ReadCities() const override;
private:
	INIReader reader_;
};

