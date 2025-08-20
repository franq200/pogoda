#include "IHttpPoller.h"

IHttpPoller::IHttpPoller(const std::string& url, int intervalSeconds):
	url_(url), intervalSeconds_(intervalSeconds)
{
}
