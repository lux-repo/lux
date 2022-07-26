#pragma once
#include <type_traits>

namespace hui {
    namespace tools {

        template < template <auto...> class base, typename derived>
        struct is_base_of_template
        {
        private:
            template<auto... Ts>
            static constexpr std::true_type  __impl(const base<Ts...>*);
            static constexpr std::false_type __impl(...);
            using type = decltype(__impl(std::declval<derived*>()));
        public:
            static constexpr bool value = type::value;
        };

        /**
        * get parameters list (tuple) from a variadic template class
        */
        template< class T >
        struct parameters_pack
        {
        private:
            template<template<typename...> class G, typename... Ts>
            static constexpr auto __impl(const G<Ts...>*)
            {
                return std::tuple<Ts...>();
            }
        public:
            using type = decltype(__impl(std::declval<T*>()));
        };

    }
}