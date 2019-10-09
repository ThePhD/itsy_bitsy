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

#ifndef ITSY_BITSY_SMALL_BIT_VECTOR_HPP
#define ITSY_BITSY_SMALL_BIT_VECTOR_HPP

#include <itsy/version.hpp>

#include <itsy/detail/small_bit_vector.hpp>

#include <memory>
#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	inline constexpr ::std::size_t default_small_buffer_size_v =
	     ITSY_BITSY_DETAIL_NAMESPACE::__default_small_buffer_size_v<T, Allocator>;

	template<typename Word,
	     ::std::size_t InlineBufferSize = default_small_buffer_size_v<Word, std::allocator<Word>>,
	     typename Allocator             = std::allocator<Word>>
	using small_bit_vector =
	     ITSY_BITSY_DETAIL_NAMESPACE::__small_bit_vector<Word, InlineBufferSize, Allocator>;
} // namespace bitsy

#endif // ITSY_BITSY_SMALL_BIT_VECTOR_HPP
