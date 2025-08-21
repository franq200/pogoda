#pragma once
#include <string>
#include "IHttpPoller.h"

class HttpPoller : public IHttpPoller
{
public:
	HttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser, std::vector<std::string>& cities);//zmieniæ nazwê na weatherhttppoller
private:
	void Poll() override;
	WeatherData response_;
};


