#pragma once
#include "IWeatherIniReader.h"

class WeatherIniReader : public IWeatherIniReader
{
public:
	std::vector<std::string> ReadCities(const std::string& path) const override;
};

