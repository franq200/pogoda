#pragma once
#include "IIniReader.h"
#include <INIReader.h>

class DataCollectorIniReader : public IIniReader
{
public:
	DataCollectorIniReader(const std::string& path);
	std::vector<std::string> GetValues(const std::string& section, const std::string& key) const override;
	std::string GetValue(const std::string& section, const std::string& key) const override;
private:
	INIReader reader_;
};

