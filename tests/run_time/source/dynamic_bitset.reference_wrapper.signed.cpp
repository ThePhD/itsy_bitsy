// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <itsy_tests/shared_insert_erase_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("dynamic_bitset reference_wrapper bulk insert test, signed",
  "[dynamic_bitset][reference_wrapper][bulk][insert][signed]", std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char, signed char, std::ptrdiff_t)
{
	SECTION("vector")
	{
		std::vector<TestType> backing_storage;
		{
			bitsy::bit_sequence<std::reference_wrapper<std::vector<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("std::basic_string")
	{
		std::basic_string<TestType> backing_storage;
		{
			bitsy::bit_sequence<std::reference_wrapper<std::basic_string<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("deque")
	{
		std::deque<TestType> backing_storage;
		{
			bitsy::bit_sequence<std::reference_wrapper<std::deque<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("list")
	{
		std::list<TestType> backing_storage;
		{
			bitsy::bit_sequence<std::reference_wrapper<std::list<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
}
