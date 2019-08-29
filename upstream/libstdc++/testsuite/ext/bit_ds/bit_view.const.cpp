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

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

template<typename TestType, bool check_iterator_comparisons = true, typename Storage,
  typename OnIndices, typename OffIndices>
void
bit_view_const_test(Storage& storage, OnIndices& on_indices, OffIndices& off_indices,
  std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>)
{
	using span_range = std::span<TestType>;
	using R          = span_range;

	if constexpr (check_iterator_comparisons)
		{
			REQUIRE(std::size(storage) == expected_words);
			bitsy::bit_view<R> truncated_view_bits(&storage[0], std::size(storage) / 2);
			REQUIRE(truncated_view_bits.size() == expected_bits / 2);
			REQUIRE(truncated_view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits / 2));
		}

	bitsy::bit_view<R> view_bits(storage);
	REQUIRE(view_bits.size() == expected_bits);
	REQUIRE(view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits));

	bit_view_test_mixed_any_all_none(view_bits);
	bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices, expected_bits);
	if constexpr (check_iterator_comparisons)
		{
			bit_view_test_iterator_comparisons(view_bits);
		}
}

template<typename TestType>
void
bit_ds_test_case_bit_view_const_span()
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 1, 2, 3, 4, 5, 6,
		5 + 2 * bitsy::binary_digits_v<TestType>, 3 + 8 * bitsy::binary_digits_v<TestType>,
		3 + 12 * bitsy::binary_digits_v<TestType>, 7 + 17 * bitsy::binary_digits_v<TestType>,
		4 + 23 * bitsy::binary_digits_v<TestType> };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0, 0 + 2 * bitsy::binary_digits_v<TestType>,
		0 + 7 * bitsy::binary_digits_v<TestType>, 0 + 12 * bitsy::binary_digits_v<TestType>,
		0 + 17 * bitsy::binary_digits_v<TestType>, 0 + 22 * bitsy::binary_digits_v<TestType>,
		0 + 27 * bitsy::binary_digits_v<TestType>, 1 + 29 * bitsy::binary_digits_v<TestType> };

	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	SECTION("vector")
	{
		const std::vector<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
			b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		bit_view_const_test<const TestType, true>(storage, on_indices, off_indices);
	}
	SECTION("std::array")
	{
		const std::array<TestType, expected_words> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00,
			b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b10 };
		bit_view_const_test<const TestType, true>(storage, on_indices, off_indices);
	}
	SECTION("std::basic_string")
	{
		const std::basic_string<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00,
			b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b10 };
		bit_view_const_test<const TestType, true>(storage, on_indices, off_indices);
	}
	SECTION("c array")
	{
		const TestType storage[expected_words]{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
			b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b10 };
		bit_view_const_test<const TestType, true>(storage, on_indices, off_indices);
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_case_bit_view_const_span<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte,
	  std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char,
	  signed char, std::size_t, std::ptrdiff_t>();
	return 0;
}
