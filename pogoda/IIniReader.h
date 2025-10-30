#pragma once
#include <vector>
#include <string>

class IIniReader
{
public:
	virtual ~IIniReader() = default;
	virtual std::vector<std::string> GetValues(const std::string& section, const std::string& key) const = 0;
	virtual std::string GetValue(const std::string& section, const std::string& key) const = 0;
};

