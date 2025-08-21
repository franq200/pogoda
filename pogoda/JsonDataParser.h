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
private:
	void from_json(const nlohmann::json& j, T& w)
	{
		w.windSpeed = j.at("current_condition")[0].at("windspeedKmph").get<std::string>();
		w.temperature = j.at("current_condition")[0].at("temp_C").get<std::string>();
		w.humidity = j.at("current_condition")[0].at("humidity").get<std::string>();
		w.location = j.at("nearest_area")[0].at("areaName")[0].at("value").get<std::string>();
	}
	void to_json(nlohmann::json& j, const T& w) const
	{
		j = nlohmann::json
		{
			{"current_condition", nlohmann::json::array({nlohmann::json{
					{"windspeedKmph", w.windSpeed},
					{"temp_C", w.temperature},
					{"humidity", w.humidity}}})},
			{"nearest_area", nlohmann::json::array({nlohmann::json{
					{"areaName", nlohmann::json::array({
						nlohmann::json{{"value", w.location}}})}}})}
		};
	}
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
