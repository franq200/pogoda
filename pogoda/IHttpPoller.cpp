#include "IHttpPoller.h"

IHttpPoller::IHttpPoller(const std::string& url, int intervalSeconds, IDataParser<WeatherData>& dataParser, std::vector<std::string>& cities):
	url_(url), intervalSeconds_(intervalSeconds), dataParser_(dataParser)
{
}
