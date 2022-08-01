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

#include <ztd/idk/version.hpp>

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
