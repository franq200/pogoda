#pragma once
#include "IIniReader.h"

class IniReader : public IIniReader
{
public:
	std::vector<std::string> ReadCities(const std::string& path) const override;
private:
	void RemoveUnnecessaryCharacters(std::string& city) const;
};

