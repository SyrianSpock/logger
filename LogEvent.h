#include <ctime>

#include "Displayable.h"

struct LogEvent
{
    LogEvent(const std::time_t& _time, const std::string& _callerName, int _callerLine, Displayable&& _event)
          : time(_time)
          , callerName(_callerName)
          , callerLine(_callerLine)
          , event(std::move(_event))
    {
    }

    std::time_t time;
    std::string callerName;
    int callerLine;
    Displayable event;
};

std::string dateTime(const time_t& now)
{
    struct tm* tstruct = localtime(&now);

    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", tstruct);

    return buf;
}

void display(const LogEvent& log)
{
    std::cout << "[" << dateTime(log.time) << "]";
    std::cout << "[" << log.callerName << ":" << log.callerLine << "]";
    std::cout << " ";
    display(log.event);
}
