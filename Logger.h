#include "LogEvent.h"

#define LOG_ERROR(logger, event) (logger.record(LogLevel::Error, std::time(0), __FUNCTION__, __LINE__, event))
#define LOG_WARN(logger, event) (logger.record(LogLevel::Warning, std::time(0), __FUNCTION__, __LINE__, event))
#define LOG_INFO(logger, event) (logger.record(LogLevel::Info, std::time(0), __FUNCTION__, __LINE__, event))
#define LOG_DEBUG(logger, event) (logger.record(LogLevel::Debug, std::time(0), __FUNCTION__, __LINE__, event))

class Logger
{
public:
    Logger() = default;

    void record(LogLevel level, const std::time_t& time, const std::string& callerName, int callerLine,
                Displayable&& event)
    {
        m_events.emplace_back(level, time, callerName, callerLine, std::move(event));
    }

    void displayEvents(LogLevel severityLevel) const
    {
        for (const auto& event : m_events)
        {
            if (event.level <= severityLevel)
            {
                display(event);
            }
        }
    }

private:
    std::vector<LogEvent> m_events;
};
