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

#ifndef ITSY_BITSY_BIT_OPERATIONS_HPP
#define ITSY_BITSY_BIT_OPERATIONS_HPP

#include <itsy/version.hpp>

#include <itsy/detail/bit_operations.hpp>

namespace bitsy
{
	template<typename T>
	using binary_digits = ITSY_BITSY_SOURCE_NAMESPACE::__binary_digits<T>;

	template<typename T>
	inline constexpr auto binary_digits_v = binary_digits<T>::value;

	template<typename T, typename Size>
	constexpr Size
	bit_to_element_size(Size bit_size)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_to_element_size<T>(bit_size);
	}

	template<typename T, typename Size>
	constexpr Size
	element_to_bit_size(Size element_size)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__element_to_bit_size<T>(element_size);
	}

	namespace detail
	{
		using ITSY_BITSY_SOURCE_NAMESPACE::__shift_and_preserve;
		using ITSY_BITSY_SOURCE_NAMESPACE::__shift_left_preserve_left;
		using ITSY_BITSY_SOURCE_NAMESPACE::__shift_left_preserve_right;
		using ITSY_BITSY_SOURCE_NAMESPACE::__shift_right_preserve_left;
		using ITSY_BITSY_SOURCE_NAMESPACE::__shift_right_preserve_right;

		template<typename _Type>
		using any_to_underlying_t = ITSY_BITSY_SOURCE_NAMESPACE::__any_to_underlying_t<_Type>;

		template<typename _Integralish>
		constexpr auto
		to_underlying_if_enum_or_char_t(_Integralish __val) noexcept
		{
			return ITSY_BITSY_SOURCE_NAMESPACE::__to_underlying_if_enum_or_char_t(__val);
		}
	} // namespace detail

	template<typename Integralish>
	constexpr int
	countl_zero(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_countl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countl_one(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_countl_one(value);
	}

	template<typename Integralish>
	constexpr int
	countr_zero(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_countr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countr_one(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_countr_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_zero(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_firstl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_one(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_firstl_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_zero(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_firstr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_one(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_firstr_one(value);
	}

	template<typename Integralish>
	constexpr int
	popcount(Integralish value)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__bit_popcount(value);
	}

	template<typename Position, typename Mask>
	constexpr Position
	mask_to_position(Mask mask)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__mask_to_pos<Position>(mask);
	}

	template<typename Mask, typename Position>
	constexpr Mask
	position_to_mask(Position position)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__pos_to_mask<Mask>(position);
	}

	template<typename Integralish, typename Position>
	constexpr Integralish
	merge_lsb_and_msb_at(Integralish lsbits, Integralish msbits, Position position)
	{
		return ITSY_BITSY_SOURCE_NAMESPACE::__merge_bits_at(lsbits, msbits, position);
	}
} // namespace bitsy

#endif // ITSY_BITSY_BIT_OPERATIONS_HPP