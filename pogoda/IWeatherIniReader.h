#pragma once
#include <vector>
#include <string>

class IWeatherIniReader
{
public:
	virtual ~IWeatherIniReader() = default;
	virtual std::vector<std::string> ReadCities(const std::string& filename) const = 0;
};

