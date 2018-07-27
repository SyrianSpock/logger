#include <ctime>
#include <map>

#include "Displayable.h"

struct LogEvent
{
    enum class Level
    {
        Error,
        Warning,
        Info,
        Debug,
    };

    LogEvent(Level _level, const std::time_t& _time, const std::string& _callerName, int _callerLine,
             Displayable&& _event)
          : level(_level)
          , time(_time)
          , callerName(_callerName)
          , callerLine(_callerLine)
          , event(std::move(_event))
    {
    }

    Level level;
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

std::string toString(const LogEvent::Level& level)
{
    return std::map<LogEvent::Level, std::string>{
        {LogEvent::Level::Error, "ERROR"}, {LogEvent::Level::Warning, "WARNING"}, {LogEvent::Level::Info, "INFO"},
        {LogEvent::Level::Debug, "DEBUG"}}[level];
}

void display(const LogEvent& log)
{
    std::cout << "[" << dateTime(log.time) << "]";
    std::cout << "[" << toString(log.level) << "]";
    std::cout << "[" << log.callerName << ":" << log.callerLine << "]";
    std::cout << " ";
    display(log.event);
}
