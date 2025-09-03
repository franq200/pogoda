#pragma once
#include "IDataParser.h"
#include <string>
#include <nlohmann/json.hpp>

template <typename T>
class JsonDataParser : public IDataParser<T>
{
public:
	std::string Serialize(const T& data) const override;
	T Deserialize(const std::string& data) const override;
};

template<typename T>
inline std::string JsonDataParser<T>::Serialize(const T& data) const
{
	nlohmann::json jsonData = data;
	return jsonData.dump();
}

template<typename T>
inline T JsonDataParser<T>::Deserialize(const std::string& data) const
{
	nlohmann::json jsonData = nlohmann::json::parse(data);
	return jsonData.get<T>();
}
