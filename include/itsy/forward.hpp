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

#ifndef ITSY_BITSY_FORWARD_HPP
#define ITSY_BITSY_FORWARD_HPP

#include <itsy/version.hpp>

#include <cstddef>

namespace bitsy
{

	template<typename _Type>
	class bit_mask_type;

	template<typename _Type>
	using bit_mask_type_t = typename bit_mask_type<_Type>::type;

	class bit_value;
	template<typename, typename>
	class bit_reference;
	template<typename>
	class bit_pointer;
	template<typename>
	class bit_iterator;

	template<typename Range>
	class word_bit_bounds;

	template<typename Range>
	class dynamic_bit_bounds_for;

	template<std::size_t first, std::size_t last>
	class bit_bounds;

	class dynamic_bit_bounds;

	template<typename, typename Bounds>
	class bit_view;

	template<typename, ::std::size_t, typename, bool>
	class basic_small_bit_vector;

	template<typename, ::std::size_t, typename>
	class packed_small_bit_vector;

	template<typename, ::std::size_t, typename>
	class small_bit_vector;

	template<typename>
	class bit_sequence;

	template<typename, typename>
	class bit_vector;

} // namespace bitsy

#endif // ITSY_BITSY_FORWARD_HPP
