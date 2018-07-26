#include "Displayable.h"

struct LogEvent
{
    LogEvent(const std::string& _callerName, Displayable&& _event)
          : callerName(_callerName)
          , event(std::move(_event))
    {
    }

    std::string callerName;
    Displayable event;
};

void display(const LogEvent& log)
{
    std::cout << "[" << log.callerName << "]";
    std::cout << " ";
    display(log.event);
}

class Logger
{
public:
    Logger() = default;

    void record(const std::string& callerName, Displayable&& event)
    {
        m_events.emplace_back(callerName, std::move(event));
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
