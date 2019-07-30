#pragma once

#ifndef BITSY_BIT_ITERATOR_HPP
#define BITSY_BIT_ITERATOR_HPP

#include <cstddef>
#include <cstdint>

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
// <ThePhD>: __GLIBCXX__ is in compressed ISO date format as an Unsigned Long
// compare to September 1st, 2019 to know if GSOC finished.
// Should have been merged by this time, anyways,
// but this is past me, calling out future me if I fail :D

// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <bits/bit_iterator.h>

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 11000
// _LIBCPP_VERSION is VER_NUMBER RELEASE_NUM, where VER_NUMBER is
// the latest version and RELEASE_NUM is
// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <bit_iterator.h>

#else

#define __BIT_STRUCTURES_NAMESPACE __std_detail
#include <itsy/detail/bit_buffer.h>

#endif

namespace bitsy
{
	template<typename Word, ::std::size_t InlineBufferSize>
	using bit_buffer = __BIT_STRUCTURES_NAMESPACE::__bit_buffer<Word, InlineBufferSize>;
} // namespace bitsy

#endif // BITSY_BIT_ITERATOR_HPP
