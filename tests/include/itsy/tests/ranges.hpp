// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

// ranges shim for std libraries that haven't caught up

#ifndef ITSY_BITSY_TESTS_RANGES_HPP
#define ITSY_BITSY_TESTS_RANGES_HPP

#include <cstddef>

#if defined(__has_include) && __has_include(<ranges>) && ((ITSY_BITSY_LIBSTDCXX == 0) || __cplusplus > 201709L) && ITSY_BITSY_VCXX == 0 && ITSY_BITSY_CLANG == 0

#include <ranges>

namespace bitsy::tests
{
	using ::std::ranges::subrange;
	using ::std::ranges::subrange_kind;
} // namespace bitsy::tests

#elif defined(__has_include) && __has_include(<range/v3/view/subrange.hpp>)

#include <range/v3/view/subrange.hpp>

namespace bitsy::tests
{
	using ::ranges::subrange;
	using ::ranges::subrange_kind;
} // namespace bitsy::tests

#else

#error "Cannot get a proper ranges library for this platform"

#endif

#endif // ITSY_BITSY_TESTS_RANGES_HPP
