#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class Displayable
{
public:
    Displayable() = default;

    Displayable(const Displayable&) = delete;
    Displayable(Displayable&&) = default;

    template <typename T>
    Displayable(T&& impl) : m_impl(new model_t<std::decay_t<T>>(std::forward<T>(impl))) {}

    Displayable& operator=(const Displayable&) = delete;
    Displayable& operator=(Displayable&&) = default;

    template <typename T>
    Displayable& operator=(T&& impl)
    {
        m_impl.reset(new model_t<std::decay_t<T>>(std::forward<T>(impl)));
        return *this;
    }

    friend void display(const Displayable& d)
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
