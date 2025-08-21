#include "HttpPoller.h"
#include <Windows.h>
#include <curl/curl.h>
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
	size_t totalSize = size * nmemb;
	response->append((char*)contents, totalSize);
	return totalSize;
}

HttpPoller::HttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser, std::vector<std::string>& cities) : IHttpPoller(url, intervalSeconds, dataParser, cities)
{
}

void HttpPoller::Poll()
{
	CURL* curl = curl_easy_init();
	if (curl)
	{
		CURLcode res;
		std::string response;
		curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
		curl_easy_cleanup(curl);
		response_ = dataParser_.Deserialize(response);
	}
	Sleep(intervalSeconds_ * 1000);
}
