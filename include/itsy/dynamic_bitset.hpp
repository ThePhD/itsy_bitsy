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

#ifndef ITSY_BITSY_DYNAMIC_BITSET_HPP
#define ITSY_BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#include <itsy/bit_sequence.hpp>

#include <cstddef>
#include <vector>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	using dynamic_bitset = bit_sequence<std::vector<T, Allocator>>;
} // namespace bitsy

#endif // ITSY_BITSY_DYNAMIC_BITSET_HPP
