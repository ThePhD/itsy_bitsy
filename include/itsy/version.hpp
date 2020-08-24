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

#if (defined(__has_include) && __has_include(<version>)) || (__cplusplus >= 202000L)
#include <version>
#endif

// clang-format off

#define itsy_bitsy_bit_iterator 201908L
#define itsy_bitsy_bit_view 201908L
#define itsy_bitsy_dynamic_bit_set 201908L

#define ITSY_BITSY_IS_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) != 0)
#define ITSY_BITSY_IS_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3) == 0)
#define ITSY_BITSY_IS_DEFAULT_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) > 3)
#define ITSY_BITSY_IS_DEFAULT_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3 OP_SYMBOL 3) < 0)

#define ITSY_BITSY_ON          |
#define ITSY_BITSY_OFF         ^
#define ITSY_BITSY_DEFAULT_ON  +
#define ITSY_BITSY_DEFAULT_OFF -

#if defined(__clang__)

#define ITSY_BITSY_GCC_I_   ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_CLANG_I_ ITSY_BITSY_DEFAULT_ON
#define ITSY_BITSY_VCXX_I_  ITSY_BITSY_DEFAULT_OFF

#elif defined(__GNUC__)

#define ITSY_BITSY_GCC_I_   ITSY_BITSY_DEFAULT_ON
#define ITSY_BITSY_CLANG_I_ ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_VCXX_I_  ITSY_BITSY_DEFAULT_OFF

#else

#define ITSY_BITSY_GCC_I_   ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_CLANG_I_ ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_VCXX_I_  ITSY_BITSY_DEFAULT_ON

#endif

#if defined(__GLIBCXX__)

#define ITSY_BITSY_LIBSTDCXX_I_ ITSY_BITSY_DEFAULT_ON
#define ITSY_BITSY_LIBCXX_I_    ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_LIBVCXX_I_   ITSY_BITSY_DEFAULT_OFF

#elif defined(_LIBCPP_VERSION)

#define ITSY_BITSY_LIBSTDCXX_I_ ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_LIBCXX_I_    ITSY_BITSY_DEFAULT_ON
#define ITSY_BITSY_LIBVCXX_I_   ITSY_BITSY_DEFAULT_OFF

#elif defined(_YVALS_H_) || defined(_YVALS_CORE_H_)

#define ITSY_BITSY_LIBSTDCXX_I_ ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_LIBCXX_I_    ITSY_BITSY_DEFAULT_ON
#define ITSY_BITSY_LIBVCXX_I_   ITSY_BITSY_DEFAULT_OFF

#else

#define ITSY_BITSY_LIBSTDCXX_I_ ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_LIBCXX_I_    ITSY_BITSY_DEFAULT_OFF
#define ITSY_BITSY_LIBVCXX_I_   ITSY_BITSY_DEFAULT_OFF

#endif

#if defined(ITSY_BITSY_SOURCE_NAMESPACE)
	#define ITSY_BITSY_EXTERNAL_SOURCE_I_  ITSY_BITSY_ON
	#define ITSY_BITSY_SOURCE_NAMESPACE_I_ ITSY_BITSY_SOURCE_NAMESPACE
#else
	#if ITSY_BITSY_IS_ON(ITSY_BITSY_LIBSTDCXX_I_) && defined(__gnu_cxx_bit_extensions) && (__gnu_cxx_bit_extensions != 0)
		#define ITSY_BITSY_EXTERNAL_SOURCE_I_ ITSY_BITSY_ON
		#define ITSY_BITSY_SOURCE_NAMESPACE   __gnu_cxx
	#else
		#define ITSY_BITSY_EXTERNAL_SOURCE_I_ ITSY_BITSY_OFF
		#define ITSY_BITSY_SOURCE_NAMESPACE   bitsy::__detail
	#endif
#endif

#if defined(ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS)
	#if ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS != 0
		#define ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT)
	#if ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT != 0
		#define ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(__cpp_char8_t)
	#if __cpp_char8_t != 0
		#define ITSY_BITSY_STD_CHAR8_T_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_STD_CHAR8_T_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_STD_CHAR8_T_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(__cpp_lib_to_address)
	#if __cpp_lib_to_address != 0
		#define ITSY_BITSY_STD_LIB_TO_ADDRESS_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_STD_LIB_TO_ADDRESS_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_STD_LIB_TO_ADDRESS_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(__cpp_lib_bitops)
	#if __cpp_lib_bitops != 0
		#define ITSY_BITSY_STD_LIB_BIT_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_STD_LIB_BIT_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_STD_LIB_BIT_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(__cpp_lib_span)
	#if __cpp_lib_span != 0
		#define ITSY_BITSY_STD_LIB_SPAN_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_STD_LIB_SPAN_I_ ITSY_BITSY_OFF
	#endif
#else
	#define ITSY_BITSY_STD_LIB_SPAN_I_ ITSY_BITSY_DEFAULT_OFF
#endif

#if defined(ITSY_BITSY_USE_RANGEV3_SPAN)
	#if ITSY_BITSY_USE_RANGEV3_SPAN != 0
		#define ITSY_BITSY_USE_RANGEV3_SPAN_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_USE_RANGEV3_SPAN_I_ ITSY_BITSY_OFF
	#endif
#else
	#if defined(__has_include) && __has_include(<range/v3/view/span.hpp>)
		#define ITSY_BITSY_USE_RANGEV3_SPAN_I_ ITSY_BITSY_DEFAULT_ON
	#else
		#define ITSY_BITSY_USE_RANGEV3_SPAN_I_ ITSY_BITSY_DEFAULT_OFF
	#endif
#endif

#if defined(ITSY_BITSY_USE_NONSTD_SPAN)
	#if ITSY_BITSY_USE_NONSTD_SPAN != 0
		#define ITSY_BITSY_USE_NONSTD_SPAN_I_ ITSY_BITSY_ON
	#else
		#define ITSY_BITSY_USE_NONSTD_SPAN_I_ ITSY_BITSY_OFF
	#endif
#else
	#if defined(__has_include) && __has_include(<nonstd/span.hpp>)
		#define ITSY_BITSY_USE_NONSTD_SPAN_I_ ITSY_BITSY_DEFAULT_ON
	#else
		#define ITSY_BITSY_USE_NONSTD_SPAN_I_ ITSY_BITSY_DEFAULT_OFF
	#endif
#endif

// clang-format on

namespace bitsy
{
	// Decimal:
	// 100          = revision
	// 100 XXX      = minor
	// 100 XXX XXX  = major
	inline constexpr std::uint64_t tag_version = 100200000;
	// YYYYDD feature-macro like value
	inline constexpr std::uint64_t feature_version = 202008L;
} // namespace bitsy

#endif // ITSY_BITSY_VERSION_HPP
