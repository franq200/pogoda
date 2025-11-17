#include "WeatherHttpPoller.h"
#include "IDataParser.h"
#include "Logger.h"
#include <iostream>

WeatherHttpPoller::WeatherHttpPoller(std::unique_ptr<IDataParser<WeatherData>> dataParser)
	: dataParser_(std::move(dataParser))
{
	curl_ = curl_easy_init();
	if (!curl_)
	{
		throw std::runtime_error("Failed to initialize Weather CURL");
	}
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, IHttpPoller::WriteCallback);
}

WeatherHttpPoller::~WeatherHttpPoller()
{
	if (curl_)
	{
		curl_easy_cleanup(curl_);
	}
}

std::unique_ptr<IHttpPoller::PollResult> WeatherHttpPoller::Poll(const std::string& url)
{
	auto logger = Logger::GetInstance();
	std::string response;
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());

	CURLcode res = curl_easy_perform(curl_);
	if (res != CURLE_OK)
	{
		logger->LogError("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
		return {};
	}
	response_ = std::make_unique<WeatherData>( dataParser_->Deserialize(response));

	logger->LogInfo("Location: " + response_->location +
		"Temperature: " + response_->temperature +
		"Humidity: " + response_->humidity + 
		"Wind Speed: " + response_->windSpeed +
		"Time: " + response_->localTime);

	std::cerr<< "Location: " << response_->location << "\n"
			  << "Temperature: " << response_->temperature << "\n"
			  << "Humidity: " << response_->humidity << "\n"
			<< "Wind Speed: " << response_->windSpeed << "\n"
			<< "Time:" << response_->localTime << "\n\n";

	return std::move(response_);
}
