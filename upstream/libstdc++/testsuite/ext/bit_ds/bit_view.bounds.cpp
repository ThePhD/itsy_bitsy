// bit data structures extension tests -*- C++ -*-

// Copyright (C) 2019-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file testsuite/ext/bit_ds/algorithm.cpp
 *  This file tests a GNU extension to the Standard C++ Library.
 */

#include <bit_ds_constants.hpp>
#include <bit_ds_tests_shared_tests.hpp>

#include <bit_ds_tests_require.h>

#include <ext/bit>

#include <cstddef>
#include <cstdint>
#include <span>
#include <ranges>
#include <iterator>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

TEMPLATE_TEST_CASE("bit_view bounds testing", "[bit_view<T>][span][bounds]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 1, 2, 3, 4, 5, 6 };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0 };

	constexpr std::size_t expected_bits = 15;

	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	SECTION("vector")
	{
		std::vector<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(storage, on_indices, off_indices, expected_bits);
	}
	SECTION("deque")
	{
		std::deque<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(storage, on_indices, off_indices, expected_bits);
	}
	SECTION("deque")
	{
		std::deque<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(storage, on_indices, off_indices, expected_bits);
	}
}
