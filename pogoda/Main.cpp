#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Logger.h"
#include "WeatherIniReader.h"

struct WeatherData
{
	std::string location;
	std::string temperature;
	std::string humidity;
	std::string windSpeed;
};

size_t WriteCallbackM(void* contents, size_t size, size_t nmemb, std::string* response) 
{
	size_t totalSize = size * nmemb;
	response->append((char*)contents, totalSize);
	return totalSize;
}

void from_json(const nlohmann::json& j, WeatherData& w)
{
	w.windSpeed = j.at("current_condition")[0].at("windspeedKmph").get<std::string>();
	w.temperature = j.at("current_condition")[0].at("temp_C").get<std::string>();
	w.humidity = j.at("current_condition")[0].at("humidity").get<std::string>();
	w.location = j.at("nearest_area")[0].at("areaName")[0].at("value").get<std::string>();
}
void to_json(nlohmann::json& j, const WeatherData& w)
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

int main()
{
	/*
	CURL* curl = curl_easy_init();
	if (curl) 
	{
		CURLcode res;
		std::string response;
		curl_easy_setopt(curl, CURLOPT_URL, "https://wttr.in/Warsaw?format=j1");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackM);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
		curl_easy_cleanup(curl);
		nlohmann::json j = nlohmann::json::parse(response);
		WeatherData w = j.get<WeatherData>();
		std::cout << w.location << "\n" << w.temperature << '\n' << w.humidity << '\n' << w.windSpeed;
	}
	curl_global_cleanup();
	*/
	WeatherIniReader iniReader;
	auto cities = iniReader.ReadCities("../config.ini");
	for (auto& i : cities)
	{
		std::cout << "City: " << i << "\n";
	}
	auto logger = Logger::GetInstance();
	logger->LogError("Test error message");

	return 0;
}