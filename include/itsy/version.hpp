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

#define itsy_bitsy_bit_iterator 201908L
#define itsy_bitsy_bit_view 201908L
#define itsy_bitsy_dynamic_bit_set 201908L

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

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20191201UL

#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE __gnu_cxx
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 1
#define ITSY_BITSY_SOURCE_LIBCXX 0
#define ITSY_BITSY_SOURCE_LIBVCXX 0

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 12000

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
