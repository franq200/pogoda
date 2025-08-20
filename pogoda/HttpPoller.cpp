#include "HttpPoller.h"
#include <Windows.h>

HttpPoller::HttpPoller(const std::string& url, int intervalSeconds) : IHttpPoller(url, intervalSeconds)
{
}

void HttpPoller::Poll()
{
}
