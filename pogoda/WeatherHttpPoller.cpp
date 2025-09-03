#include "WeatherHttpPoller.h"
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
	size_t totalSize = size * nmemb;
	response->append((char*)contents, totalSize);
	return totalSize;
}

WeatherHttpPoller::WeatherHttpPoller(std::unique_ptr<IDataParser<WeatherData>> dataParser)
	: dataParser_(std::move(dataParser))
{
	curl_ = curl_easy_init();
	if (!curl_)
	{
		throw std::runtime_error("Failed to initialize CURL");
	}
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
}

WeatherHttpPoller::~WeatherHttpPoller()
{
	if (curl_)
	{
		curl_easy_cleanup(curl_);
	}
}

void WeatherHttpPoller::Poll(const std::string& url)
{
	std::string response;
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());

	CURLcode res = curl_easy_perform(curl_);
	if (res != CURLE_OK)
	{
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
	}
	response_ = dataParser_->Deserialize(response);

	std::cout << "Location: " << response_.location << "\n"
			  << "Temperature: " << response_.temperature << "\n"
			  << "Humidity: " << response_.humidity << "\n"
			<< "Wind Speed: " << response_.windSpeed << "\n\n";
}
