#include <vector>
#include <variant>

namespace lux {

	template< template<typename...> class CRTPBase, class... Args>
	class CRTPVector : public std::vector<std::variant<Args...>>
	{
	public:
		using std::vector<std::variant<Args...>>::vector;

		template<class _Callable>
		void inline for_each(_Callable&& _func)
		{
			for (auto& item : *this) std::visit(std::forward<_Callable>(_func), item);
		}

	private:
		template<size_t I, typename typeC, class... typeL >
		static constexpr typename std::enable_if < I < sizeof...(Args) - 1, bool>::type _type_check()
		{
			if constexpr (
				is_base_of_template<CRTPBase, typeC>::value &&
				std::is_base_of<CRTPBase<typeC>, typeC>::value
				)
			{
				return _type_check<I + 1, typeL ...>();
			}
			return false;
		}

		template<size_t I, typename typeC>
		static constexpr typename std::enable_if< I == sizeof...(Args) - 1, bool>::type _type_check()
		{
			return  is_base_of_template<CRTPBase, typeC>::value &&
				std::is_base_of<CRTPBase<typeC>, typeC>::value;
		}

		static_assert(CRTPVector::_type_check<0, Args...>(), "[CRTP]: Not all type T dervied from template Base<T>");
	};
}