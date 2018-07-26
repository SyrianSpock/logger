#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class LogEvent
{
public:
    LogEvent() = default;

    LogEvent(const LogEvent&) = delete;
    LogEvent(LogEvent&&) = default;

    template <typename T>
    LogEvent(T&& impl) : m_impl(new model_t<std::decay_t<T>>(std::forward<T>(impl))) {}

    LogEvent& operator=(const LogEvent&) = delete;
    LogEvent& operator=(LogEvent&&) = default;

    template <typename T>
    LogEvent& operator=(T&& impl)
    {
        m_impl.reset(new model_t<std::decay_t<T>>(std::forward<T>(impl)));
        return *this;
    }

    friend void display(const LogEvent& d)
    {
        d.m_impl->do_display();
    }

private:
    struct concept_t
    {
        virtual ~concept_t() {}
        virtual void do_display() const = 0;
    };
    template <typename T>
    struct model_t : public concept_t
    {
        model_t() = default;
        model_t(const T& v) : m_data(v) {}
        model_t(T&& v) : m_data(std::move(v)) {}

        void do_display() const override
        {
            display(m_data);
        }

        T m_data;
    };

    std::unique_ptr<concept_t> m_impl;
};
