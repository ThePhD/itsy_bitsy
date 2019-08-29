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

#ifndef ITSY_BITSY_VERSION_HPP
#define ITSY_BITSY_VERSION_HPP

#include <cstddef>
#include <cstdint>

#define ITSY_BITSY_bit_iterator 201908L
#define ITSY_BITSY_bit_view 201908L
#define ITSY_BITSY_dynamic_bit_set 201908L

#if defined(__GLIBCXX__)

#define ITSY_BITSY_LIBSTDCXX 1
#define ITSY_BITSY_LIBCXX 0
#define ITSY_BITSY_LIBVCXX 0

#elif defined(_LIBCPP_VERSION)

#define ITSY_BITSY_LIBSTDCXX 0
#define ITSY_BITSY_LIBCXX 1
#define ITSY_BITSY_LIBVCXX 0

#else

#define ITSY_BITSY_LIBSTDCXX 0
#define ITSY_BITSY_LIBCXX 0
#define ITSY_BITSY_LIBVCXX 1

#endif

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
// <ThePhD>: __GLIBCXX__ is in compressed ISO date format as an Unsigned Long
// compare to September 1st, 2019 to know if GSOC finished.
// Should have been merged by this time, anyways,
// but this is past me, calling out future me if I fail :D

// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE __gnu_cxx
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 1
#define ITSY_BITSY_SOURCE_LIBCXX 0
#define ITSY_BITSY_SOURCE_LIBVCXX 0

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 12000
// _LIBCPP_VERSION is VER_NUMBER RELEASE_NUM, where VER_NUMBER is
// the latest version and RELEASE_NUM is
// GSoC finished, propose to libc++ soon thereafter
#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE __gnu_cxx
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 0
#define ITSY_BITSY_SOURCE_LIBCXX 1
#define ITSY_BITSY_SOURCE_LIBVCXX 0

#else

#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE bitsy::detail
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 0
#define ITSY_BITSY_SOURCE_LIBCXX 0
#define ITSY_BITSY_SOURCE_LIBVCXX 1

#endif

namespace bitsy
{
	// 4 bits per MAJOR MINOR PATCH
	inline constexpr std::uint64_t tag_version = 0x010000;
	// YYYYDD feature-macro like value
	inline constexpr std::uint64_t feature_version = 201908L;
} // namespace bitsy

#endif // ITSY_BITSY_VERSION_HPP
