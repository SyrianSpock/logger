#include "Displayable.h"

class Logger
{
public:
    Logger() = default;

    void record(Displayable&& event)
    {
        m_events.push_back(std::move(event));
    }

    void displayEvents() const
    {
        for (const auto& event : m_events)
        {
            display(event);
        }
    }

private:
    std::vector<Displayable> m_events;
};
