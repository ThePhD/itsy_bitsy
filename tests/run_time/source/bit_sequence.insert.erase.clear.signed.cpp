// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/tests/shared_insert_erase_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("bit_sequence insert/erase/clear test, signed",
     "[bit_sequence][insert][erase][clear][signed]", std::int64_t, std::int32_t, std::int16_t,
     std::int8_t, char, signed char, std::ptrdiff_t)
{
	SECTION("vector")
	{
		bitsy::bit_sequence<std::vector<TestType>> storage;
		bit_sequence_insert_erase_test<TestType>(storage);
	}
	SECTION("std::basic_string")
	{
		bitsy::bit_sequence<std::basic_string<TestType>> storage;
		bit_sequence_insert_erase_test<TestType>(storage);
	}
	SECTION("deque")
	{
		bitsy::bit_sequence<std::deque<TestType>> storage;
		bit_sequence_insert_erase_test<TestType>(storage);
	}
	SECTION("list")
	{
		bitsy::bit_sequence<std::list<TestType>> storage;
		bit_sequence_insert_erase_test<TestType>(storage);
	}
}
