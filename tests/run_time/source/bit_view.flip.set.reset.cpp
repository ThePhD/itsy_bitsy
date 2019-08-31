// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy_tests/constants.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

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

TEMPLATE_TEST_CASE("bit_view modifiers flip, set and reset", "[bit_view<T>][modifiers]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t,
     std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char,
     std::size_t, std::ptrdiff_t)
{
	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	std::vector<TestType> truth_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
		b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
		b10 };
	bitsy::bit_view<std::span<TestType>> truth(truth_storage);
	std::list<TestType> truth_list_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
		b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
		b10 };
	auto truth_list_range = std::ranges::make_subrange(truth_list_storage);
	bitsy::bit_view<decltype(truth_list_range)> truth_list(truth_list_range);

	SECTION("vector")
	{
		std::vector<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00,
			b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
			b01, b00, b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::array")
	{
		std::array<TestType, expected_words> backing_storage{ b01, b00, b01, b00, b00, b00, b00,
			b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
			b00, b00, b00, b01, b00, b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::basic_string")
	{
		std::basic_string<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00,
			b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
			b00, b01, b00, b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("c array")
	{
		TestType backing_storage[expected_words]{ b01, b00, b01, b00, b00, b00, b00, b01, b00,
			b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
			b00, b01, b00, b10 };
		bitsy::bit_view<std::span<TestType>> storage(backing_storage);
		bit_view_test_flip_set_reset(storage, truth);
	}
	SECTION("std::list")
	{
		std::list<TestType> backing_storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00,
			b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
			b01, b00, b10 };
		auto sr = std::ranges::make_subrange(backing_storage);
		bitsy::bit_view<decltype(sr)> storage(sr);
		bit_view_test_flip_set_reset(storage, truth_list);
	}
}
