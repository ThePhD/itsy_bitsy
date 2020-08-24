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

#ifndef ITSY_BITSY_BIT_SPAN_HPP
#define ITSY_BITSY_BIT_SPAN_HPP

#include <itsy/version.hpp>

#include <itsy/bit_view.hpp>

#include <itsy/detail/span.hpp>

namespace bitsy
{
	template<typename T, typename Bounds = word_bit_bounds<::ITSY_BITSY_SOURCE_NAMESPACE::span<T>>>
	using bit_span = bit_view<::ITSY_BITSY_SOURCE_NAMESPACE::span<T>, Bounds>;
} // namespace bitsy

#endif // ITSY_BITSY_BIT_SPAN_HPP
