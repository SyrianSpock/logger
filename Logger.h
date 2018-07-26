#include "LogEvent.h"

#define LOG(logger, event) (logger.record(__FUNCTION__, __LINE__, event))

class Logger
{
public:
    Logger() = default;

    void record(const std::string& callerName, int callerLine, Displayable&& event)
    {
        m_events.emplace_back(callerName, callerLine, std::move(event));
    }

    void displayEvents() const
    {
        for (const auto& event : m_events)
        {
            display(event);
        }
    }

private:
    std::vector<LogEvent> m_events;
};
