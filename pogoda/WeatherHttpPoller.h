#pragma once
#include "IHttpPoller.h"

#include <string>
#include <curl/curl.h>
#include <memory>
#include <nlohmann/json.hpp>

template<typename T>
class IDataParser;

struct PollResult
{
	std::string location;
	std::string temperature;
	std::string humidity;
	std::string windSpeed;
};
using WeatherData = PollResult;

inline void from_json(const nlohmann::json& j, WeatherData& w)
{
	w.windSpeed = j.at("current_condition")[0].at("windspeedKmph").get<std::string>();
	w.temperature = j.at("current_condition")[0].at("temp_C").get<std::string>();
	w.humidity = j.at("current_condition")[0].at("humidity").get<std::string>();
	w.location = j.at("nearest_area")[0].at("areaName")[0].at("value").get<std::string>();
}
inline void to_json(nlohmann::json& j, const WeatherData& w)
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

class WeatherHttpPoller : public IHttpPoller
{
public:
	WeatherHttpPoller(std::unique_ptr<IDataParser<WeatherData>> dataParser);
	~WeatherHttpPoller() override;
	WeatherData Poll(const std::string& url) override;
private:
	CURL* curl_;
	WeatherData response_;
	std::unique_ptr<IDataParser<WeatherData>> dataParser_;
};


