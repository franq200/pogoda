#include <memory>
#include "WeatherApp.h"
#include "WeatherHttpPoller.h"
#include "WeatherIniReader.h"
#include "Logger.h"
#include "JsonDataParser.h"

int main()
{
	auto logger = Logger::GetInstance();
	WeatherApp app(std::make_unique<WeatherHttpPoller>("https://wttr.in/Warsaw?format=j1", std::make_unique<JsonDataParser<WeatherData>>()), std::make_unique<WeatherIniReader>(), logger, 5);
	app.Run();
	return 0;
}