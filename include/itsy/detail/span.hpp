// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

// span shim for libraries that have not caught up

#ifndef ITSY_BITSY_DETAIL_SPAN_HPP
#define ITSY_BITSY_DETAIL_SPAN_HPP

#include <itsy/version.hpp>

#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_LIB_SPAN_I_)

#include <span>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	using ::std::span;
}

#elif ITSY_BITSY_IS_ON(ITSY_BITSY_USE_NONSTD_SPAN_I_)

#include <nonstd/span.hpp>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	using ::nonstd::span;
}

#elif ITSY_BITSY_IS_ON(ITSY_BITSY_USE_RANGEV3_SPAN_I_)

#include <range/v3/view/span.hpp>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	using ::ranges::span;
}

#else

#error \
     "Cannot use this feature: a span of some sort is required! Please pull in the submodules or provide your own span on the include paths."

#endif // Span bullshit

#endif // ITSY_BITSY_DETAIL_SPAN_HPP
