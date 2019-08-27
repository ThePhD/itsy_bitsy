// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#pragma once

#ifndef ITSY_BITSY_BIT_OPERATIONS_HPP
#define ITSY_BITSY_BIT_OPERATIONS_HPP

#include <itsy/version.hpp>

#include <itsy/detail/bit_operations.hpp>

namespace bitsy
{
	template<typename T>
	using binary_digits = ITSY_BITSY_DETAIL_NAMESPACE::__binary_digits<T>;

	template<typename T>
	inline constexpr auto binary_digits_v = binary_digits<T>::value;

	namespace detail
	{
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_and_preserve;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_left_preserve_left;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_left_preserve_right;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_right_preserve_left;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_right_preserve_right;

		template<typename _Type>
		using any_to_underlying_t = ITSY_BITSY_DETAIL_NAMESPACE::__any_to_underlying_t<_Type>;

		template<typename _Integralish>
		auto
		to_underlying_if_enum_or_char_t(_Integralish __val)
		{
			return ITSY_BITSY_DETAIL_NAMESPACE::__to_underlying_if_enum_or_char_t(__val);
		}
	} // namespace detail

	template<typename Integralish>
	constexpr int
	countl_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__countl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countl_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__countl_one(value);
	}

	template<typename Integralish>
	constexpr int
	countr_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__countr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countr_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__countr_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__firstl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__firstl_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__firstr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__firstr_one(value);
	}

	template<typename Integralish>
	constexpr int
	popcount(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__popcount(value);
	}

	template<typename Position, typename Mask>
	constexpr Position
	mask_to_position(Mask mask)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__mask_to_pos<Position>(mask);
	}

	template<typename Mask, typename Position>
	constexpr Mask
	position_to_mask(Position position)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__pos_to_mask<Mask>(position);
	}

	template<typename Integralish, typename Position>
	constexpr Integralish
	merge_lsb_and_msb_at(Integralish lsbits, Integralish msbits, Position position)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__merge_bits_at(lsbits, msbits, position);
	}
} // namespace bitsy

#endif // ITSY_BITSY_BIT_OPERATIONS_HPP