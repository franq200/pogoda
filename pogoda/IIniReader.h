#pragma once
#include <vector>
#include <string>

class IIniReader
{
public:
	virtual ~IIniReader() = default;
	virtual std::vector<std::string> ReadCities(const std::string& filename) const = 0;
};

