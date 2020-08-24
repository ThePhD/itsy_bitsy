// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("bit_sequence assign test, signed", "[bit_sequence][assign][signed]", std::int64_t,
     std::int32_t, std::int16_t, std::int8_t, char, signed char, std::ptrdiff_t)
{
	SECTION("normal")
	{
		bitsy::dynamic_bitset<TestType> source0(100, false);
		bitsy::dynamic_bitset<TestType> source1(150, true);
		bitsy::dynamic_bitset<TestType> destination0;
		bitsy::dynamic_bitset<TestType> destination1;
		destination0 = source0;
		destination1 = source1;
		REQUIRE(destination0 == source0);
		REQUIRE(destination1 == source1);
	}
	SECTION("packed")
	{
		bitsy::packed_dynamic_bitset<TestType> source0(100, false);
		bitsy::packed_dynamic_bitset<TestType> source1(150, true);
		bitsy::packed_dynamic_bitset<TestType> destination0;
		bitsy::packed_dynamic_bitset<TestType> destination1;
		destination0 = source0;
		destination1 = source1;
		REQUIRE(destination0 == source0);
		REQUIRE(destination1 == source1);
	}
}

TEMPLATE_TEST_CASE("bit_sequence assign test, signed", "[bit_sequence][assign][unsigned]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char, std::size_t)
{
	SECTION("normal")
	{
		bitsy::dynamic_bitset<TestType> source0(100, false);
		bitsy::dynamic_bitset<TestType> source1(150, true);
		bitsy::dynamic_bitset<TestType> destination0;
		bitsy::dynamic_bitset<TestType> destination1;
		destination0 = source0;
		destination1 = source1;
		REQUIRE(destination0 == source0);
		REQUIRE(destination1 == source1);
	}
	SECTION("packed")
	{
		bitsy::packed_dynamic_bitset<TestType> source0(100, false);
		bitsy::packed_dynamic_bitset<TestType> source1(150, true);
		bitsy::packed_dynamic_bitset<TestType> destination0;
		bitsy::packed_dynamic_bitset<TestType> destination1;
		destination0 = source0;
		destination1 = source1;
		REQUIRE(destination0 == source0);
		REQUIRE(destination1 == source1);
	}
}
