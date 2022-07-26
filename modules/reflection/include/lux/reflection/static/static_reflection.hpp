#pragma once
/**
 * @file StaticReflection.hpp
 * @author chenhui.yu
 * @brief
 * @version 0.1
 * @date 2022-02-07
 *
 * @copyright Copyright (c) 2022
 */

#include "lux/string/mpstring.hpp"
#include "field.hpp"

#include <memory>
#include <string_view>
#include <tuple>

namespace lux
{
    namespace reflection
    {
        /*
        sample:
            // You can define a class/struct:
            struct TestClass
            {
                int			ElementOne;
                double		ElementTwo;
                std::string ElementThree;
            
                int func(int a, int b)
                {
                    return a + b;
                }
            };
            
            // Then regist type infomation
            using TestClassInfo =
            lux::reflection::StaticTypeInfo<
                TestClass,
                MAKE_FIELD(&TestClass::ElementOne,   "ElementOne"),
                MAKE_FIELD(&TestClass::ElementTwo,   "ElementTwo"),
                MAKE_FIELD(&TestClass::ElementThree, "ElementThree"),
                MAKE_FIELD(&TestClass::func,		 "func")
            >;
        */
        template<class T, class... Fields>
        class StaticTypeInfo
        {
        public:
            using type = T;
            constexpr static size_t fields_num = sizeof...(Fields);

        private:
            using tuple_type = std::tuple<Fields...>;

            constexpr static tuple_type fields_list{};

            template<class Func, size_t... I>
            constexpr static inline void _for_each_fields(Func&& func, std::index_sequence<I...>)
            {
                (func( std::get<I>(fields_list) ), ...);
            }

            template<class FieldT, class Name>
            struct is_same_field_name : std::bool_constant< std::is_same_v< typename FieldT::mp_string, Name > > {};

            template<typename Name, size_t I = 0>
            constexpr static auto _find_field_index()
            {
                static_assert(I < fields_num, "Field name is not in this type info");
                using compare_rst = decltype(is_same_field_name< std::tuple_element_t<I, tuple_type>, Name>());
                if constexpr (compare_rst::value)
                    return std::integral_constant<size_t, I>{};
                else
                    return _find_field_index<Name, I + 1>();
            }

        public:
            
            template<typename Name>
            constexpr static auto find_field_index() -> decltype(_find_field_index<Name, 0>());
               
            /*
                If you has registed a type named TestClassInfo

                Then you can visit every field by:
                
                TestClassInfo::forEachFields(
                    [](auto&& field)
                    {
                        using field_type = std::decay_t<decltype(field)>;
                        std::cout << field_type::name << std::endl;

                        // Because std::string_view has constexpr constructor,
                        // you can compare member name at compile time and invoke a member function
                        if constexpr (field_type::name == std::string_view("func"))
                        {
                            TestClass tmp_obj;
                            auto ret_value = field_type::invoke(&tmp_obj, 1, 2);
                            std::cout << "func return :" << ret_value << std::endl;
                        }
                    }
                );
            */
            template<class Func>
            constexpr static void forEachFields(Func&& func)
            {
                _for_each_fields(std::forward<Func>(func), std::make_index_sequence<fields_num>());
            }

            template<class Name>
            using field_index = decltype(find_field_index<Name>());

            template<class Name>
            using find_field = std::tuple_element_t< field_index<Name>::value, tuple_type >;
        };

    }
}