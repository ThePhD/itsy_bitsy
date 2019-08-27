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

#ifndef ITSY_BITSY_BIT_VIEW_HPP
#define ITSY_BITSY_BIT_VIEW_HPP

#include <itsy/version.hpp>
#include <itsy/bit_iterator.hpp>

#include <itsy/detail/bit_view.hpp>

namespace bitsy
{
	template<typename Range>
	using word_bit_bounds = ITSY_BITSY_DETAIL_NAMESPACE::__word_bit_bounds<Range>;

	template<typename Range>
	using dynamic_bit_bounds_for = ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds_for<Range>;

	template<std::size_t first, std::size_t last>
	using bit_bounds = ITSY_BITSY_DETAIL_NAMESPACE::__bit_bounds<first, last>;

	using dynamic_bit_bounds = ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds;

	template<typename Range, typename Bounds = word_bit_bounds<Range>>
	using bit_view = ITSY_BITSY_DETAIL_NAMESPACE::__bit_view<Range, Bounds>;

} // namespace bitsy

#endif // ITSY_BITSY_BIT_VIEW_HPP
