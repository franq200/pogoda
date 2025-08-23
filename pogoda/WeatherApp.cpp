#include "WeatherApp.h"

WeatherApp::WeatherApp(const std::string& url, IDataParser<WeatherData>& dataParser, int intervalSeconds, std::vector<std::string>& cities)
	: cities_(cities), intervalSeconds_(intervalSeconds), poller_(url, dataParser)
{
}

void WeatherApp::Run()
{
}
