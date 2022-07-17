// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_DETAIL_BIT_DETAIL_HPP
#define ITSY_BITSY_DETAIL_BIT_DETAIL_HPP 1

#include <itsy/version.hpp>

#include <itsy/forward.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/unwrap.hpp>
#include <ztd/ranges/adl.hpp>
#include <ztd/idk/to_mutable_iter.hpp>

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>
#include <memory>
#include <functional>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	struct __dummy_tag
	{
	};

	template<typename Alloc, typename... Args>
	using __allocator_construct_invocable_test =
	     decltype(::std::declval<Alloc>().construct(::std::declval<Args>()...));

	template<typename _Type>
	union alignas(_Type) __uninit
	{
		constexpr __uninit() : _M_dummy()
		{
		}

		template<typename... _Args>
		constexpr __uninit(::std::in_place_t, _Args&&... __args) : _M_value(::std::forward<_Args>(__args)...)
		{
		}

		char _M_dummy;
		_Type _M_value;
	};

	template<typename _Type, typename = void>
	class __un_binary_digits
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_integral_v<_Type>>>
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<_Type>::digits>
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_enum_v<_Type>>>
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits>
	{
	};

	template<typename _Type>
	class __binary_digits : public __un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	inline constexpr auto __binary_digits_v = __binary_digits<_Type>::value;

	template<typename _Type>
	inline constexpr auto __max_binary_index_v = __binary_digits_v<_Type> - 1;

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	__bit_to_element_size(_SizeType __bit_size)
	{
		return static_cast<_SizeType>((__bit_size + __max_binary_index_v<_Type>) / __binary_digits_v<_Type>);
	}

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	__element_to_bit_size(_SizeType __element_size)
	{
		return static_cast<_SizeType>(__element_size * __binary_digits_v<_Type>);
	}

	template<typename, typename = void>
	class __un_bit_mask_type
	{
	};

	template<typename _Type>
	class __un_bit_mask_type<_Type, std::enable_if_t<std::is_integral_v<_Type> || std::is_enum_v<_Type>>>
	{
	public:
		using type = _Type;
	};

	template<typename _Type>
	class __bit_mask_type : public __un_bit_mask_type<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	using __bit_mask_type_t = typename __bit_mask_type<_Type>::type;

	template<typename _It>
	struct __is_bit_iterator : ::std::false_type
	{
	};

	template<typename _It>
	struct __is_bit_iterator<__bit_iterator<_It>> : ::std::true_type
	{
	};

	template<typename _It>
	inline constexpr bool __is_bit_iterator_v = __is_bit_iterator<_It>::value;

	template<typename _Target, typename _Actual>
	using __is_iterator_category_or_better = ::std::is_base_of<_Target, _Actual>;

	template<typename _Target, typename _Actual>
	inline constexpr bool __is_iterator_category_or_better_v =
	     __is_iterator_category_or_better<_Target, _Actual>::value;

	template<typename _LeftType, typename _RightType>
	inline constexpr bool __is_same_no_cvref_v =
	     ::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_LeftType>>,
	          ::std::remove_cv_t<::std::remove_reference_t<_RightType>>>;

	template<typename _Enumish, typename = void>
	struct __any_to_underlying
	{
		using type = _Enumish;
	};

	template<typename _Enumish>
	struct __any_to_underlying<_Enumish, ::std::enable_if_t<::std::is_enum_v<_Enumish>>>
	{
		using type = ::std::underlying_type_t<_Enumish>;
	};

	template<typename _Enumish>
	using __any_to_underlying_t = typename __any_to_underlying<_Enumish>::type;

	template<typename _Integralish>
	inline constexpr auto
	__to_underlying_if_enum(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish>)
			{
				return static_cast<::std::underlying_type_t<_Integralish>>(__val);
			}
		else
			{
				return __val;
			}
	}

	template<typename _Integralish>
	inline constexpr auto
	__to_underlying_if_enum_or_char_t(_Integralish __val) noexcept
	{
		if constexpr (::std::is_same_v<_Integralish, char>)
			{
				using _UTy =
				     ::std::conditional_t<::std::is_signed_v<char>, ::std::int_least8_t, ::std::uint_least8_t>;
				return static_cast<_UTy>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, wchar_t>)
			{
				if constexpr (::std::is_signed_v<wchar_t>)
					{
						if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least8_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least8_t, ::std::uint_least8_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least16_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least16_t, ::std::uint_least16_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least32_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least32_t, ::std::uint_least32_t>;
								return static_cast<_UTy>(__val);
							}
						else
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least64_t, ::std::uint_least64_t>;
								return static_cast<_UTy>(__val);
							}
					}
				else
					{
						return static_cast<uint_least8_t>(__val);
					}
			}
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_CHAR8_T_I_)
		else if constexpr (::std::is_same_v<_Integralish, char8_t>)
			{
				return static_cast<unsigned char>(__val);
			}
#endif // char8_t
		else if constexpr (::std::is_same_v<_Integralish, char16_t>)
			{
				return static_cast<uint_least16_t>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, char32_t>)
			{
				return static_cast<uint_least32_t>(__val);
			}
		else
			{
				return __to_underlying_if_enum(__val);
			}
	}

	template<typename _Type>
	using __has_size_function_test = decltype(::std::declval<_Type&>().size());

	template<typename _Left, typename _Right = _Left>
	using __equal_to_test = decltype(::std::declval<_Left&>() == ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __not_equal_to_test = decltype(::std::declval<_Left&>() != ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __less_than_test = decltype(::std::declval<_Left&>() < ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __less_equal_to_test = decltype(::std::declval<_Left&>() <= ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __greater_than_test = decltype(::std::declval<_Left&>() > ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __greater_equal_to_test = decltype(::std::declval<_Left&>() >= ::std::declval<_Right&>());

	template<typename _Container>
	using __has_value_type_test = decltype(_Container::value_type);

	template<typename _Type>
	using __has_pair_iterator_insert_test =
	     decltype(::std::declval<_Type&>().insert(::ztd::ranges::ranges_adl::adl_cbegin(::std::declval<_Type&>()),
	          ::ztd::ranges::ranges_adl::adl_cbegin(::std::declval<_Type&>()), ::ztd::ranges::ranges_adl::adl_cend(::std::declval<_Type&>())));

	template<typename _Container, typename = void>
	class __is_bit_container_test : public ::std::false_type
	{
	};

	template<typename _Container>
	class __is_bit_container_test<_Container, ::std::enable_if_t<::ztd::is_detected_v<__has_value_type_test, _Container>>>
	: public ::std::integral_constant<bool, ::std::is_same_v<typename _Container::value_type, __bit_value>>
	{
	};

	template<typename _Container>
	class __is_bit_container : ::std::integral_constant<bool, __is_bit_container_test<_Container>::value>
	{
	};

	template<typename _Container>
	inline constexpr bool __is_bit_container_v = __is_bit_container<_Container>::value;

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_BIT_DETAIL_HPP
