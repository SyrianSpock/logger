#include "Displayable.h"

struct LogEvent
{
    LogEvent(const std::string& _callerName, int _callerLine, Displayable&& _event)
          : callerName(_callerName)
          , callerLine(_callerLine)
          , event(std::move(_event))
    {
    }

    std::string callerName;
    int callerLine;
    Displayable event;
};

void display(const LogEvent& log)
{
    std::cout << "[" << log.callerName << ":" << log.callerLine << "]";
    std::cout << " ";
    display(log.event);
}

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
