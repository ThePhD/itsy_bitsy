#pragma once

#ifndef BITSY_VERSION_HPP
#define BITSY_VERSION_HPP

#include <cstddef>
#include <cstdint>

#define bitsy_bit_iterator 201908L
#define bitsy_bit_view 201908L
#define bitsy_dynamic_bit_set 201908L

#if defined(__GLIBCXX__)

#define BITSY_LIBSTDCXX 1
#define BITSY_LIBCXX 0
#define BITSY_LIBVCXX 0

#elif defined(_LIBCPP_VERSION)

#define BITSY_LIBSTDCXX 0
#define BITSY_LIBCXX 1
#define BITSY_LIBVCXX 0

#else

#define BITSY_LIBSTDCXX 0
#define BITSY_LIBCXX 0
#define BITSY_LIBVCXX 1

#endif

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
// <ThePhD>: __GLIBCXX__ is in compressed ISO date format as an Unsigned Long
// compare to September 1st, 2019 to know if GSOC finished.
// Should have been merged by this time, anyways,
// but this is past me, calling out future me if I fail :D

// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx

#define BITSY_SOURCE_LIBSTDCXX 1
#define BITSY_SOURCE_LIBCXX 0
#define BITSY_SOURCE_LIBVCXX 0

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 12000
// _LIBCPP_VERSION is VER_NUMBER RELEASE_NUM, where VER_NUMBER is
// the latest version and RELEASE_NUM is
// GSoC finished, propose to libc++ soon thereafter
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx

#define BITSY_SOURCE_LIBSTDCXX 0
#define BITSY_SOURCE_LIBCXX 1
#define BITSY_SOURCE_LIBVCXX 0

#else

#define __BIT_STRUCTURES_NAMESPACE __std_detail

#define BITSY_SOURCE_LIBSTDCXX 0
#define BITSY_SOURCE_LIBCXX 0
#define BITSY_SOURCE_LIBVCXX 1

#endif

namespace bitsy
{
	// 4 bits per MAJOR MINOR PATCH
	inline constexpr std::uint64_t tag_version = 0x010000;
	// YYYYDD feature-macro like value
	inline constexpr std::uint64_t feature_version = 201908L;
} // namespace bitsy

#endif // BITSY_VERSION_HPP
