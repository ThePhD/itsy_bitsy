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

#ifndef ITSY_BITSY_DYNAMIC_BITSET_HPP
#define ITSY_BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#include <itsy/bit_sequence.hpp>
#include <itsy/small_bit_vector.hpp>

#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	using dynamic_bitset =
	     small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator>;
} // namespace bitsy

#endif // ITSY_BITSY_DYNAMIC_BITSET_HPP
