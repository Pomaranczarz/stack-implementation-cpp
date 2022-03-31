#pragma once

#ifndef __cpp_concepts
#warning message("Stack.hpp: C++20 concepts are not available")
#else

#include <deque>
#include <type_traits>

template<typename T>
concept StackCompatibleContainer = requires (T container) {
    container.push_back(std::declval<typename T::value_type>());
    container.pop_back();
    container.back();
    container.size();
    container.empty();
};

template<typename T, StackCompatibleContainer Container = std::deque<T>>
    requires std::is_same_v<T, typename Container::value_type>
class Stack
{
public:
    using value_type = typename Container::value_type;
    using ref_type = value_type&;
    using const_ref_type = const value_type&;

    void push(value_type&& value) {
        m_data.push_back(value);
    }

    void push(const_ref_type value) {
        m_data.push_back(value);
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        m_data.emplace_back(args...);
    }

    template<typename... Args>
    ref_type emplace_back(Args&&... args) {
        return m_data.emplace_back(args...);
    }

    [[nodiscard]] ref_type top() {
        return m_data.back();
    }

    [[nodiscard]] const_ref_type top() const {
        return m_data.back();
    }

    value_type pop() {
        auto retval = m_data.back();
        m_data.pop_back();

        return retval;
    }

    [[nodiscard]] bool empty() const noexcept {
        return m_data.empty();
    }

    [[nodiscard]] size_t size() const noexcept {
        return m_data.size();
    }

    void swap(Stack& other) noexcept {
        m_data.swap(other.m_data);
    }

private:
    Container m_data;
};

#endif // __cpp_concepts
