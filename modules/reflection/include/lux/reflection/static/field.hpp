#pragma once
#include "lux/type_tools/function_tools.hpp"

namespace lux
{
	namespace reflection
	{
        enum class MemberType
        {
            Object,
            Function
        };

        template<MemberType I>
        struct MemberTypeIntegral { MemberType value = I; };

        template<class T>
        struct to_member_type
        {
        private:
            template<class U>
            constexpr static std::enable_if_t < 
                std::is_member_function_pointer_v<U>, 
                MemberTypeIntegral<MemberType::Function>
            > _member_type();

            template<class U>
            constexpr static std::enable_if_t < 
                std::is_member_object_pointer_v<U>, 
                MemberTypeIntegral<MemberType::Object>  
            > _member_type();

        public:
            using type = decltype(_member_type<T>());
        };

        template<class T, class Name, MemberType I>
        class _field_base
        {
        private:
            template<class MemType, class ClassType>
            constexpr static auto _get_mem_type(MemType ClassType::*&&) ->MemType*;

            template<class MemType, class ClassType>
            constexpr static auto _get_class_type(MemType ClassType::*&&) ->ClassType*;
        public:
            using   class_type  = std::remove_pointer_t<decltype(_get_class_type(std::declval<T>()))>;
            using   member_type = std::remove_pointer_t<decltype(_get_mem_type(std::declval<T>()))>;
            using   mp_string   = Name;

            constexpr static std::string_view   name{ Name::data, Name::N - 1 };
            constexpr static MemberType         member_id{ I };
        };

        template<auto _member_pointer, class Name, class U>
        class Field;

        template<auto _member_pointer, class Name>
        class Field<_member_pointer, Name, MemberTypeIntegral<MemberType::Object> >
            : public _field_base< decltype(_member_pointer), Name, MemberType::Object>
        {
        public:
            constexpr static inline typename Field::member_type& object(typename Field::class_type& instance)
            {
                return instance.*_member_pointer;
            }
        };

        template<auto _member_pointer, class Name>
        class Field<_member_pointer, Name, MemberTypeIntegral<MemberType::Function> >
            : public _field_base<decltype(_member_pointer), Name, MemberType::Function>
        {
        public:
            template<typename... Args>
            constexpr static inline auto invoke(typename Field::class_type* instance, Args&&... args)
            {
                return (instance->*_member_pointer)(std::forward<Args>(args)...);
            }
        };
	}
}

#define FIELD_NAME(name)\
MAKE_MPSTRING(name)

#define MAKE_FIELD(elem_type, element_name)\
lux::reflection::Field<elem_type, FIELD_NAME(element_name), typename lux::reflection::to_member_type<decltype(elem_type)>::type >
