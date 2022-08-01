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

#ifndef ITSY_BITSY_BINARY_DIGITS_HPP
#define ITSY_BITSY_BINARY_DIGITS_HPP 1

#include <itsy/version.hpp>

#include <itsy/forward.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/unwrap.hpp>
#include <ztd/ranges/adl.hpp>
#include <ztd/idk/to_mutable_iter.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <iterator>
#include <type_traits>
#include <utility>
#include <memory>
#include <functional>

namespace bitsy
{
	namespace __ib_detail
	{

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
		: public ::std::integral_constant<::std::size_t,
		       ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits>
		{
		};

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

	} // namespace __ib_detail

	template<typename _Type>
	class binary_digits : public __ib_detail::__un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	inline constexpr auto binary_digits_v = binary_digits<_Type>::value;

	namespace __ib_detail
	{
		template<typename _Type>
		inline constexpr auto __max_binary_index_v = binary_digits_v<_Type> - 1;
	}

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	bit_to_element_size(_SizeType __bit_size)
	{
		return static_cast<_SizeType>(
		     (__bit_size + __ib_detail::__max_binary_index_v<_Type>) / binary_digits_v<_Type>);
	}

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	element_to_bit_size(_SizeType __element_size)
	{
		return static_cast<_SizeType>(__element_size * binary_digits_v<_Type>);
	}

	template<typename _Type>
	class bit_mask_type : public __ib_detail::__un_bit_mask_type<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	using bit_mask_type_t = typename bit_mask_type<_Type>::type;

} // namespace bitsy

#endif // ITSY_BITSY_BINARY_DIGITS_HPP
