#pragma once

#ifndef BITSY_BIT_VIEW_HPP
#define BITSY_BIT_VIEW_HPP

#include <cstddef>
#include <cstdint>

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
// <ThePhD>: __GLIBCXX__ is in compressed ISO date format as an Unsigned Long
// compare to September 1st, 2019 to know if GSOC finished.
// Should have been merged by this time, anyways,
// but this is past me, calling out future me if I fail :D

// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <bits/bit_view.h>

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 11000
// _LIBCPP_VERSION is VER_NUMBER RELEASE_NUM, where VER_NUMBER is
// the latest version and RELEASE_NUM is
// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <bit_view.h>

#else

#define __BIT_STRUCTURES_NAMESPACE __std_detail
#include <itsy/detail/bit_view.h>

#endif

#include <itsy/bit_iterator.hpp>

namespace bitsy
{
	template<typename Range>
	using word_bit_extents = __BIT_STRUCTURES_NAMESPACE::__word_bit_extents<Range>;

	template<typename Range>
	using dynamic_bit_extents_for = __BIT_STRUCTURES_NAMESPACE::__dynamic_bit_extents_for<Range>;

	template<std::size_t first, std::size_t last>
	using static_bit_extents = __BIT_STRUCTURES_NAMESPACE::__static_bit_extents<first, last>;

	using dynamic_bit_extents = __BIT_STRUCTURES_NAMESPACE::__dynamic_bit_extents;

	template<typename R, typename Extents = word_bit_extents<R>>
	using bit_view = __BIT_STRUCTURES_NAMESPACE::__bit_view<R, Extents>;
} // namespace bitsy

#endif // BITSY_BIT_VIEW_HPP
