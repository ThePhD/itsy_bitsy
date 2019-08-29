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

#include <bit_ds_tests_require.h>

#include <ext/bit>

#include <cstddef>
#include <cstdint>
#include <span>
#include <ranges>
#include <iterator>

#include <vector>
#include <array>
#include <string>
#include <list>

template<typename Sequence, typename Truth>
void
bit_view_test_flip_set_reset(Sequence& sequence, Truth& truth)
{
	{
		auto it       = sequence.cbegin();
		auto truth_it = truth.cbegin();
		auto last     = sequence.cend();
		for (; it != last; ++it, ++truth_it)
			{
				bool val          = *it;
				bool expected_val = *truth_it;
				REQUIRE(val == expected_val);
			}
		REQUIRE(truth_it == truth.cend());
	}
	sequence.flip();
	{
		auto it       = sequence.cbegin();
		auto truth_it = truth.cbegin();
		auto last     = sequence.cend();
		for (; it != last; ++it, ++truth_it)
			{
				bool val          = *it;
				bool expected_val = !*truth_it;
				REQUIRE(val == expected_val);
			}
		REQUIRE(truth_it == truth.cend());
	}
	sequence.flip();
	{
		auto it       = sequence.cbegin();
		auto truth_it = truth.cbegin();
		auto last     = sequence.cend();
		for (; it != last; ++it, ++truth_it)
			{
				bool val          = *it;
				bool expected_val = *truth_it;
				REQUIRE(val == expected_val);
			}
		REQUIRE(truth_it == truth.cend());
	}

	sequence.reset();
	{
		auto it   = sequence.cbegin();
		auto last = sequence.cend();
		for (; it != last; ++it)
			{
				bool val          = *it;
				bool expected_val = false;
				REQUIRE(val == expected_val);
			}
	}
	sequence.set();
	{
		auto it   = sequence.cbegin();
		auto last = sequence.cend();
		for (; it != last; ++it)
			{
				bool val          = *it;
				bool expected_val = true;
				REQUIRE(val == expected_val);
			}
	}
	sequence.set(false);
	{
		auto it   = sequence.cbegin();
		auto last = sequence.cend();
		for (; it != last; ++it)
			{
				bool val          = *it;
				bool expected_val = false;
				REQUIRE(val == expected_val);
			}
	}
	sequence.set(true);
	{
		auto it   = sequence.cbegin();
		auto last = sequence.cend();
		for (; it != last; ++it)
			{
				bool val          = *it;
				bool expected_val = true;
				REQUIRE(val == expected_val);
			}
	}
}

template<typename TestType>
void
bit_ds_test_case_bit_view_modifiers()
{
	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	std::vector<TestType> truth_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
		b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
	bitsy::bit_view<std::span<TestType>> truth(truth_storage);
	std::list<TestType> truth_list_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
		b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
	auto truth_list_range = std::ranges::make_subrange(truth_list_storage);
	bitsy::bit_view<decltype(truth_list_range)> truth_list(truth_list_range);

	SECTION("vector")
	{
		std::vector<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
			b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::array")
	{
		std::array<TestType, expected_words> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
			b01, b00, b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::basic_string")
	{
		std::basic_string<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00,
			b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("c array")
	{
		TestType backing_storage[expected_words]{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
			b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::list")
	{
		std::list<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
			b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		auto sr = std::ranges::make_subrange(backing_storage);
		bitsy::bit_view<decltype(sr)> storage(sr);
		bit_view_test_flip_set_reset(storage, truth_list);
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_case_bit_view_span<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte,
	  std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char,
	  signed char, std::size_t, std::ptrdiff_t>();
	return 0;
}
