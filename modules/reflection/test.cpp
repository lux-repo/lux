#include "lux/reflection/static/static_reflection.hpp"
#include <iostream>
#include <string>

struct TestClass
{
	int			ElementOne{5};
	double		ElementTwo;
	std::string ElementThree;

	int func(int a, int b)
	{
		return a + b + ElementOne;
	}
};

using TestClassInfo =
lux::reflection::StaticTypeInfo<
	TestClass,
	MAKE_FIELD(&TestClass::ElementOne,   "ElementOne"),
	MAKE_FIELD(&TestClass::ElementTwo,   "ElementTwo"),
	MAKE_FIELD(&TestClass::ElementThree, "ElementThree"),
	MAKE_FIELD(&TestClass::func,		 "func")
>;

int main(int argc, char* argv[])
{
	TestClassInfo::forEachFields(
		[](auto&& field)
		{
			using field_type = std::decay_t<decltype(field)>;
			std::cout << field_type::name << std::endl;

			if constexpr (field_type::name == std::string_view("func"))
			{
				TestClass tmp_obj;
				auto ret_value = field_type::invoke(&tmp_obj, 1, 2);
				std::cout << "func return :" << ret_value << std::endl;
			}
		}
	);

	return 0;
}
