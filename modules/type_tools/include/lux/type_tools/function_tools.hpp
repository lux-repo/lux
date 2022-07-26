#pragma once
#include <type_traits>
#include <functional>

template<typename T> struct function_traits;

template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
    template <size_t i>
    struct arg
    {
        using type =  std::tuple_element_t<i, std::tuple<Args...>>;
    };

    constexpr static size_t nargs = sizeof...(Args);
    using return_type = R;
};
